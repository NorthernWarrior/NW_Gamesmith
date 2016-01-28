#include "SpriteRenderer.h"

#include <nw/gfx/rendering2D/Renderable2D.h>

#include <GL/glew.h>
#include <iostream>

using namespace nw;
using namespace gfx;
using namespace math;

SpriteRenderer::SpriteRenderer() :
	m_IndexCount(0)
	, m_SpriteCount(0)
{
	glGenVertexArrays(1, &m_VAO);
	if (m_VAO == 0)
	{
		// TODO: Log!
		std::cout << "[BatchSpriteRenderer] Failed to generate VertexArray and Buffer!" << std::endl;
		return;
	}

	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

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

void SpriteRenderer::Submit(const Renderable2D* renderable)
{
	if (m_Buffer == nullptr || renderable == nullptr)
		return;

	if (m_SpriteCount >= RENDERER_MAX_SPRITES)
	{
		Unbind();
		Display();
		Bind();
	}

	const uint color = renderable->GetColor();
	const math::Vector2& pos = renderable->GetPosition();
	const math::Vector2& size = renderable->GetSize();

	// Vertex - Top Left
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(0, 1);
	m_Buffer->vertex = Vector3(pos.x - (size.x / 2.f), pos.y - (size.y / 2.f), 0);
	++m_Buffer;

	// Vertex - Top Right
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(1, 1);
	m_Buffer->vertex = Vector3(pos.x + (size.x / 2.f), pos.y - (size.y / 2.f), 0);
	++m_Buffer;

	// Vertex - Bottom Right
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(1, 0);
	m_Buffer->vertex = Vector3(pos.x + (size.x / 2.f), pos.y + (size.y / 2.f), 0);
	++m_Buffer;

	// Vertex - Bottom Left
	m_Buffer->color = color;
	m_Buffer->uv = Vector2(0, 0);
	m_Buffer->vertex = Vector3(pos.x - (size.x / 2.f), pos.y + (size.y / 2.f), 0);
	++m_Buffer;

	m_IndexCount += 6;
	++m_SpriteCount;
}

void SpriteRenderer::Unbind()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteRenderer::Display()
{
	if (m_IBO == nullptr)
		return;

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_IBO->Bind();

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_IBO->Unbind();
	glBindVertexArray(0);

	m_IndexCount = 0;
	m_SpriteCount = 0;
}
