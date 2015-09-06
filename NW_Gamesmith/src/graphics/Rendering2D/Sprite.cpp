#include "Sprite.h"

namespace gamesmith { namespace graphics {

	using namespace maths;

	Sprite::Sprite()
	{
		m_Transform = Transform2D(vec2f(), 0, vec2f(1, 1), this);
		m_Color = 0xffffffff;
		m_Size = vec2f(50, 50);
	}

	Sprite::Sprite(vec2f position, vec2f size, uint color)
	{
		m_Transform = Transform2D(position, 0, vec2f(1, 1), this);
		m_Color = color;
		m_Size = size;
	}

	Sprite::Sprite(const BoundingBox2D& bounds, uint color)
	{
		m_Transform = Transform2D(bounds.getPosition(), 0, vec2f(1, 1), this);
		m_Color = color;
		m_Size = bounds.getSize();
	}

} }