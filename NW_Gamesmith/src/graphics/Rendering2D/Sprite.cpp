#include "Sprite.h"

namespace gamesmith { namespace graphics {

	using namespace maths;

	Sprite::Sprite(vec2f position, vec2f size, uint color)
	{
		m_Position = position;
		m_Size = size;
		m_Color = color;
	}

} }