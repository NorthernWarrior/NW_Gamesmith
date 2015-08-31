#include "IndexBuffer.h"

#include <iostream>

#include <GL/glew.h>

namespace gamesmith { namespace graphics {

	IndexBuffer::IndexBuffer(const ushort* indices, uint count) :
		m_Count(count)
	{
		glGenBuffers(1, &m_ID);
		if (m_ID == 0)
		{
			// TODO: Log!
			std::cout << "[IndexBuffer] Failed to generate Buffer!" << std::endl;
			return;
		}
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(ushort), indices, GL_STATIC_DRAW);
		unbind();
	}

	IndexBuffer::~IndexBuffer()
	{
		if (m_ID > 0)
			glDeleteBuffers(1, &m_ID);
	}

	void IndexBuffer::bind() const
	{
		if (m_ID > 0)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} }