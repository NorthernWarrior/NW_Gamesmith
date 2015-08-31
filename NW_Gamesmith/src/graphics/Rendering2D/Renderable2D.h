#pragma once

#include "../../utils/typedefs.h"
#include "../../maths/Maths.h"

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
		maths::vec2f m_Position;
		maths::vec2f m_Size;

	public:
		virtual ~Renderable2D() {}

		void setColor(uint color);
		void setColor(const maths::vec4f& color);
		void setPosition(maths::vec2f pos);

		inline uint getColor() const { return m_Color; }
		inline maths::vec2f getPosition() const { return m_Position; }
		inline maths::vec2f getSize() const { return m_Size; }

	protected:
		Renderable2D() : 
			m_Color(0xffffffff), m_Position(maths::vec2f()), m_Size(1.0f, 1.0f) {}
	};

} }

