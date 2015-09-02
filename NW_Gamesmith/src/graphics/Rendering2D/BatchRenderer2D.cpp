#include "BatchRenderer2D.h"

#include <GL/glew.h>

#include "Renderable2D.h"

namespace gamesmith { namespace graphics {

	BatchRenderer2D::BatchRenderer2D() :
		m_IndexCount(0)
	{
		glGenVertexArrays(1, &m_VAO);
		if (m_VAO == 0)
		{
			// TODO: Log!
			std::cout << "[BatchRenderer2D] Failed to generate VertexArray and Buffer!" << std::endl;
			return;
		}


		glBindVertexArray(m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
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

	BatchRenderer2D::~BatchRenderer2D()
	{
		if (m_IBO != nullptr)
			delete m_IBO;
		if (m_VBO > 0)
			glDeleteBuffers(1, &m_VBO);
		if (m_VAO > 0)
			glDeleteVertexArrays(1, &m_VAO);
	}

	void BatchRenderer2D::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable)
	{
		if (m_Buffer == nullptr || renderable == nullptr)
			return;

		if (m_IndexCount >= RENDERER_INDICES_SIZE)
		{
			unbind();
			display();
			bind();
		}

		using namespace maths;

		const vec3f& position = vec3f();// = vec3f(renderable->getTransform().getPosition());
		const vec2f& size = renderable->getTransform().getScale();
		const unsigned int color = renderable->getColor();
		
		m_Buffer->vertex = (*m_TransformBack) * position;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = (*m_TransformBack) * vec3f(position.x + size.x, position.y, position.z);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = (*m_TransformBack) * vec3f(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = (*m_TransformBack) * vec3f(position.x, position.y + size.y, position.z);
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::unbind()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::display()
	{
		if (m_IBO == nullptr)
			return;

		glBindVertexArray(m_VAO); 
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_IBO->unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
	}

} }


