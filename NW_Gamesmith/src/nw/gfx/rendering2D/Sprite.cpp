#include "Sprite.h"

using namespace nw;
using namespace gfx;
using namespace math;

Sprite::Sprite()
{
}

Sprite::Sprite(Vector2 pos)
{
	m_Pos = pos;
}

Sprite::Sprite(Vector2 pos, uint color)
{
	m_Pos = pos;
	m_Color = color;
}

Sprite::Sprite(Vector2 pos, uint color, Vector2 size)
{
	m_Pos = pos;
	m_Color = color;
	m_Size = size;
}