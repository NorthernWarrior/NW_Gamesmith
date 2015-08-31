#include "Renderable2D.h"

namespace gamesmith { namespace graphics {

	void Renderable2D::setColor(uint color)
	{
		m_Color = color;
	}

	void Renderable2D::setColor(const maths::vec4f& color)
	{
		uint r = (uint)(color.r * 255.0f);
		uint g = (uint)(color.g * 255.0f);
		uint b = (uint)(color.b * 255.0f);
		uint a = (uint)(color.a * 255.0f);

		m_Color = a << 24 | b << 16 | g << 8 | r;
	}

	void Renderable2D::setPosition(maths::vec2f pos)
	{
		m_Transform.setPosition(pos);
	}

} }