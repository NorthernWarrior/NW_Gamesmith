#pragma once

#include "../../utils/typedefs.h"
#include "../../maths/Maths.h"
#include "Transform2D.h"

#include "Renderer2D.h"

namespace gamesmith { namespace graphics {
	
	struct VertexData
	{
		maths::vec3f vertex;
		uint color;
	};

	class Renderable2D
	{
	protected:
		uint m_Color;
		Transform2D m_Transform;

	public:
		virtual ~Renderable2D() {}

		virtual void onSubmit(Renderer2D* renderer) const
		{
			renderer->pushTransform(m_Transform.getMatrix());

			// TODO: This is definitely not a good solution!
			auto f = *this;
			renderer->submit(&(f));

			for (Transform2D* t : m_Transform.getChildren())
			{
				t->getRenderable()->onSubmit(renderer);
			}

			renderer->popTransform();
		}

		void setColor(uint color);
		void setColor(const maths::vec4f& color);
		void setPosition(maths::vec2f pos);

		inline uint getColor() const { return m_Color; }
		inline Transform2D* getTransform() { return &m_Transform; }

	protected:
		Renderable2D() :
			m_Color(0xffffffff), m_Transform(maths::vec2f(), 0, maths::vec2f(1.f, 1.f), this) { }
	};

} }

