#pragma once

#include "../../utils/typedefs.h"
#include "../../maths/Maths.h"
#include "Transform2D.h"

#include "Renderer2D.h"

namespace gamesmith { namespace graphics {
	
	struct VertexData
	{
		maths::vec3f vertex;
		maths::vec2f uv;
		uint color;
	};

	class Renderable2D
	{
	protected:
		uint m_Color;
		Transform2D m_Transform;
		maths::vec2f m_Size;

	public:
		virtual ~Renderable2D() {}

		virtual void onSubmit(Renderer2D* renderer) const
		{
			renderer->submit(this);

			auto childs = m_Transform.getChildren();
			if (childs.empty())
				return;

			renderer->pushTransform(m_Transform.getMatrix());

			for (int i = 0; i < childs.size(); ++i)
			{
				childs[i]->getRenderable()->onSubmit(renderer);
			}

			renderer->popTransform();
		}

		void setColor(uint color);
		void setColor(const maths::vec4f& color);
		void setPosition(maths::vec2f pos);
		void setSize(maths::vec2f size);

		inline uint getColor() const { return m_Color; }
		inline Transform2D* getTransform() { return &m_Transform; }
		inline const maths::mat4 getTransformMatrix() const { return m_Transform.getMatrix(); }
		inline const maths::vec2f getSize() const { return m_Size; }
		inline const maths::BoundingBox2D getLocalBounds() const { return maths::BoundingBox2D(maths::vec2f(), m_Size); }
		inline const maths::BoundingBox2D getGlobalBounds() const { return maths::BoundingBox2D(m_Transform.getPosition(), m_Size); }

	protected:
		Renderable2D() :
			m_Color(0xffffffff), m_Transform(maths::vec2f(), 0, maths::vec2f(1.f, 1.f), this), m_Size(maths::vec2f(1, 1)) { }
	};

} }

