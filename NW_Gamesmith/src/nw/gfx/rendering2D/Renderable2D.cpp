#include "Renderable2D.h"

using namespace nw;
using namespace gfx;
using namespace math;

void Renderable2D::SetColor(uint color)
{
	m_Color = color;
}

void Renderable2D::SetPosition(const Vector2& pos)
{
	m_Pos = pos;
}

void Renderable2D::SetSize(const Vector2& size)
{
	m_Size = size;
}