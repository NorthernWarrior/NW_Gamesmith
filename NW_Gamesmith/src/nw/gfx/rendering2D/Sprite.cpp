#include "Sprite.h"

#include <nw/Log.h>

using namespace nw;
using namespace gfx;
using namespace math;

Sprite::Sprite()
{
	m_Texture = nullptr;
}

Sprite::Sprite(const Vector2& pos)
{
	m_Pos = pos;
	m_Texture = nullptr;
}

Sprite::Sprite(const Vector2& pos, uint color)
{
	m_Pos = pos;
	m_Color = color;
	m_Texture = nullptr;
}

Sprite::Sprite(const Vector2& pos, uint color, const Vector2& size)
{
	m_Pos = pos;
	m_Color = color;
	m_Size = size;
	m_Texture = nullptr;
}

Sprite::Sprite(const Vector2& pos, const Texture2D* texture)
{
	m_Pos = pos;
	m_Color = 0xFFFFFFFF;
	m_Texture = texture;
	if (m_Texture != nullptr)
		m_Size = m_Texture->GetSize();
	else
		LOG_WARNING("[Sprite] Tried to call the constructor with a texture, but the passed texture is null!")
}