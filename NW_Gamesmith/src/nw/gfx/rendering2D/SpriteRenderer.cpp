#include "SpriteRenderer.h"

#include <nw/CommonMacros.h>
#include <nw/Log.h>

#include <nw/gfx/Camera.h>
#include <nw/gfx/Texture2D.h>

#include <nw/gfx/rendering2D/Sprite.h>
#include <nw/gfx/shader/Shader.h>

#include <nw/math/Matrix4.h>

#include <GL/glew.h>
#include <iostream>

using namespace nw;
using namespace gfx;
using namespace math;

SpriteRenderer::SpriteRenderer(Shader* shader) :
	m_IndexCount(0)
	, m_SpriteCount(0)
	, m_Shader(shader)
{
	glGenVertexArrays(1, &m_VAO);
	if (m_VAO == 0)
	{
		LOG_ERROR("[SpriteRenderer] Failed to generate VertexArray and Buffer!")
		return;
	}

	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glEnableVertexAttribArray(SHADER_TEXID_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));
	glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, texID)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ushort* indices = new ushort[RENDERER_INDICES_SIZE];
	int offset = 0;
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 0;
		indices[i + 4] = offset + 2;
		indices[i + 5] = offset + 3;

		offset += 4;
	}
	m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

	glBindVertexArray(0);

	m_Shader->Bind();
	int texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31
	};
	m_Shader->SetUniformI("tex", texIDs, 32);
}

SpriteRenderer::~SpriteRenderer()
{
	if (m_IBO != nullptr)
		delete m_IBO;
	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);
	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);
}

void SpriteRenderer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void SpriteRenderer::Submit(const Sprite* sprite)
{
	if (m_Buffer == nullptr || sprite == nullptr)
		return;

	if (m_SpriteCount >= RENDERER_MAX_SPRITES || m_TextureIDs.size() >= RENDERER_MAX_TEXTURES)
	{
		Unbind();
		Display();
		Bind();
	}

	const uint color = sprite->GetColor();
	const math::Vector2& pos = sprite->GetPosition();
	const math::Vector2& size = sprite->GetSize();

	float tid = 0;
	if (sprite->GetTexture() != nullptr)
		tid = RegisterTexture(*sprite->GetTexture());

	// Vertex - Top Left
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(0, 1);
	m_Buffer->vertex = Vector3(pos.x - (size.x / 2.f), pos.y - (size.y / 2.f), 0);
	m_Buffer->texID = tid;
	++m_Buffer;

	// Vertex - Top Right
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(1, 1);
	m_Buffer->vertex = Vector3(pos.x + (size.x / 2.f), pos.y - (size.y / 2.f), 0);
	m_Buffer->texID = tid;
	++m_Buffer;

	// Vertex - Bottom Right
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(1, 0);
	m_Buffer->vertex = Vector3(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f), 0);
	m_Buffer->texID = tid;
	++m_Buffer;

	// Vertex - Bottom Left
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(0, 0);
	m_Buffer->vertex = Vector3(pos.x - (size.x / 2.f), pos.y + (size.y / 2.f), 0);
	m_Buffer->texID = tid;
	++m_Buffer;

	m_IndexCount += 6;
	++m_SpriteCount;
}

void SpriteRenderer::Unbind()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteRenderer::Display(bool keepData)
{
	glDepthFunc(GL_NEVER);
	glDisable(GL_DEPTH_TEST);

	if (m_IBO == nullptr)
		return;

	const Camera* cam = Camera::GetActiveCamera();
	if (cam == nullptr)
		LOG_FATAL("[SpriteRenderer] Camera::ActiveCamera is NULL! Did you accidentally deleted your active camera?")

	m_Shader->Bind();
	m_Shader->SetUniformMat4("projection_matrix", cam->GetProjectionMatrix());
	m_Shader->SetUniformMat4("view_matrix", cam->GetViewMatrix());

	for (uint i = 0; i < m_TextureIDs.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TextureIDs[i]);
	}

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_IBO->Bind();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_IBO->Unbind();
	glBindVertexArray(0);

	// TODO: Come up with a better solution: Rendering for Split-Screen
	if (keepData)
		return;

	m_IndexCount = 0;
	m_SpriteCount = 0;
	m_TextureIDs.clear();
}

float SpriteRenderer::RegisterTexture(uint textureID)
{
	if (textureID < 0)
	{
		LOG_WARNING("[SpriteRenderer] RegisterTexture received an invalid TextureID: ", textureID)
		return 0;
	}

	// Iterate through all texture IDs and check if the one submitted already exists
	NW_FOR (0, m_TextureIDs.size())
	{
		auto id = m_TextureIDs[i];
		if (id == textureID)
			return static_cast<float>(i + 1);
	}

	// If not, then add it to the array and return the index
	m_TextureIDs.push_back(textureID);
	return static_cast<float>(m_TextureIDs.size());
}
float SpriteRenderer::RegisterTexture(const Texture2D& texture) 
{
	return RegisterTexture(texture.GetID());
}