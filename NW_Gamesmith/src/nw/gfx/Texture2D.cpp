#include "Texture2D.h"

#include <nw/Log.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace nw;
using namespace gfx;

Texture2D::Texture2D() :
	m_TextureID(0)
	, m_Width(0)
	, m_Height(0)
	, m_Bits(0)
{

}

Texture2D::~Texture2D()
{
	if (m_TextureID != 0)
		glDeleteTextures(1, &m_TextureID);
}

Texture2D* Texture2D::Create(uint width, uint height, uint bits, byte* pixels)
{
	if (pixels == nullptr)
	{
		LOG_ERROR("[Texture2D] Failed to create Image: Pixels must not be nullptr!")
		return nullptr;
	}
	if (width == 0 || height == 0)
	{
		LOG_ERROR("[Texture2D] Failed to create Image: Invalid sizes: Width ", width, "-  Height ", height)
		return nullptr;
	}
	if (bits != 24 && bits != 32)
	{
		LOG_ERROR("[Texture2D] Failed to create Image: Unsupported image bit-depth! ( ", bits, ")")
		return nullptr;
	}

	Texture2D* texture = new Texture2D;

	texture->m_Width = width;
	texture->m_Height = height;
	texture->m_Bits = bits;

	int internalFormat = (texture->m_Bits == 32 ? GL_RGBA : GL_RGB);
	uint imageFormat = (texture->m_Bits == 32 ? GL_BGRA : GL_BGR);

	// generate an OpenGL texture ID for this image
	glGenTextures(1, &texture->m_TextureID);
	if (texture->m_TextureID == 0)
	{
		LOG_ERROR("[Texture2D] Failed to create Image: Couldn't generate OpenGL texture!")
		delete texture;
		return nullptr;
	}

	// TODO: Some Options for filtering
	glBindTexture(GL_TEXTURE_2D, texture->m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture->m_Width, texture->m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, pixels);

	texture->Unbind();

	return texture;
}

void Texture2D::Bind() const
{
	if (m_TextureID == 0)
		return;
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}