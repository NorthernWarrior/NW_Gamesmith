#include "Transform2D.h"

using namespace nw;
using namespace gfx;
using namespace math;

Transform2D::Transform2D() :
	m_Position(Vector2::Zero())
{
}

Transform2D::Transform2D(const math::Vector2& position) :
	m_Position(position)
{
}

void Transform2D::SetPosition(const Vector2& position)
{
	if (m_Position == position)
		return;
	m_Position = position;
	CallChangedCallback();
}

void Transform2D::Translate(const Vector2& dir)
{
	m_Position += dir;
	CallChangedCallback();
}

void Transform2D::SetChangedCallback(std::function<void(const Transform2D&)> change)
{
	m_Changed = change;
}