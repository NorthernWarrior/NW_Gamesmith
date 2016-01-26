#pragma once

#include "Renderable2D.h"

namespace nw { namespace gfx {

class NW_API Sprite : public Renderable2D
{ 
public:
	Sprite();
	Sprite(math::Vector2 pos);
	Sprite(math::Vector2 pos, uint color);
	Sprite(math::Vector2 pos, uint color, math::Vector2 size);
};

} }