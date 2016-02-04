#pragma once

#include <nw/math/Vector2.h>
#include <nw/math/Vector3.h>

#include "SpriteRenderer.h"

namespace nw { namespace gfx { 

struct NW_API VertexData
{
	math::Vector3 vertex;
	math::Vector2 uv;
	uint color;
	float texID;
};

class NW_API Renderable2D
{
protected:
	Renderable2D() :
		m_Color(0xffffffff)
		, m_Pos(0.f, 0.f)
		, m_Size(1, 1)
	{
	}
	
	math::Vector2 m_Pos;
	math::Vector2 m_Size;

public:
	void SetColor(uint color);
	void SetPosition(const math::Vector2& pos);
	void SetSize(const math::Vector2& size);

	inline uint GetColor() const { return m_Color; }
	inline const math::Vector2& GetPosition() const { return m_Pos; }
	inline const math::Vector2& GetSize() const { return m_Size; }

protected:
	uint m_Color;
};

} }