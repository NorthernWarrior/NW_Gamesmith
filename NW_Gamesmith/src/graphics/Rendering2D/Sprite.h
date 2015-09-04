#pragma once

#include "Renderable2D.h"

namespace gamesmith { namespace graphics {

	class Sprite : public Renderable2D
	{
	public:
		Sprite() = default;
		Sprite(maths::vec2f position, maths::vec2f size, uint color);
		Sprite(const maths::BoundingBox2D& bounds, uint color);
	};

} }

