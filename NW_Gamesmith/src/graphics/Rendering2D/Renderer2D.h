#pragma once

#include <list>

#include "../Shader/Shader.h"

namespace gamesmith { namespace graphics {

	class Renderable2D;

	class Renderer2D
	{
	private:
		std::list<maths::mat4> m_TransformStack;
		 
	protected:
		const maths::mat4* m_TransformBack;
		
		Renderer2D()
		{
			m_TransformStack.push_back(maths::mat4::identity());
			m_TransformBack = &m_TransformStack.back();
		}

	public:
		virtual ~Renderer2D() {}

		virtual void bind() {}
		virtual void submit(Renderable2D* renderable) = 0;
		virtual void unbind() {}
		virtual void display() = 0;

		void pushTransform(const maths::mat4& matrix, bool override = false)
		{
			if (override)
				m_TransformStack.push_back(matrix);
			else
				m_TransformStack.push_back(m_TransformStack.back() * matrix);

			m_TransformBack = &m_TransformStack.back();
		}
		void popTransform()
		{
			if (m_TransformStack.size() > 1)
				m_TransformStack.pop_back();

			m_TransformBack = &m_TransformStack.back();
		}

	};

} }