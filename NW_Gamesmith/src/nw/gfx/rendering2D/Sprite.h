#pragma once

#include "Renderable2D.h"

#include <nw/gfx/Texture2D.h>

namespace nw { namespace gfx {

class NW_API Sprite : public Renderable2D
{ 
public:
	Sprite();
	Sprite(const math::Vector2& pos);
	Sprite(const math::Vector2& pos, uint color);
	Sprite(const math::Vector2& pos, uint color, const math::Vector2& size);
	Sprite(const math::Vector2& pos, const Texture2D* texture);

	inline const Texture2D* GetTexture() const { return m_Texture; }

private:
	const Texture2D* m_Texture;
};

} }