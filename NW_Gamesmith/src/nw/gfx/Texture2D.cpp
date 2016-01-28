#include "Texture2D.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace nw;
using namespace gfx;

Texture2D::Texture2D() :
	m_TextureID(0)
	, m_Width(0)
	, m_Height(0)
{

}

void Texture2D::Create(uint width, uint height, byte* pixels, uint bits)
{
	if (pixels == nullptr)
	{
		// TODO: Log!
		std::cout << "[Texture2D] Failed to create Image! Pixels must not be nullptr!" << height << std::endl;
	}
	if (width == 0 || height == 0)
	{
		// TODO: Log!
		std::cout << "[Texture2D] Failed to create Image! Invalid sizes: Width " << width << " -  Height " << height << std::endl;
	}
	if (bits != 24 && bits != 32)
	{
		// TODO: Log!
		std::cout << "[Texture2D] Failed to create Image! Unsupported image bit-depth! (" << bits << ")" << std::endl;
	}

	m_Width = width;
	m_Height = height;
	m_Bits = bits;

	int internalFormat = (m_Bits == 32 ? GL_RGBA : GL_RGB);
	uint imageFormat = (m_Bits == 32 ? GL_BGRA : GL_BGR);

	// generate an OpenGL texture ID for this image
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, pixels);
}

void Texture2D::Bind()
{
	if (m_TextureID == 0)
		return;
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}