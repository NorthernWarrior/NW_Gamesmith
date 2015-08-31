#include "Sprite.h"

namespace gamesmith { namespace graphics {

	using namespace maths;

	Sprite::Sprite(vec2f position, vec2f scale, uint color)
	{
		m_Transform = Transform2D(position, 0, scale);
		m_Color = color;
	}

} }