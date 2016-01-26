#include "IndexBuffer.h"

#include <GL/glew.h>
#include <iostream>

using namespace nw;
using namespace gfx;

IndexBuffer::IndexBuffer(const uint* indices, uint count)
{
	glGenBuffers(1, &m_ID);
	if (m_ID == 0)
	{
		// TODO: Log!
		std::cout << "[IndexBuffer] Failed to generate Buffer!" << std::endl;
		return;
	}
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), indices, GL_STATIC_DRAW);
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	if (m_ID > 0)
		glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::Bind() const
{
	if (m_ID > 0)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}