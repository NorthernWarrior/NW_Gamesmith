#pragma once

#include "../../utils/typedefs.h"
#include "../../maths/Maths.h"
#include "Transform2D.h"

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

		void setColor(uint color);
		void setColor(const maths::vec4f& color);
		void setPosition(maths::vec2f pos);

		inline uint getColor() const { return m_Color; }
		inline const Transform2D& getTransform() const { return m_Transform; }

	protected:
		Renderable2D() :
			m_Color(0xffffffff), m_Transform(maths::vec2f(), 0, maths::vec2f(1.f, 1.f)) { }
	};

} }

