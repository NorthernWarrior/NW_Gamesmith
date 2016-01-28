#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

namespace nw { namespace gfx {

class NW_API Texture2D
{
public:
	Texture2D();

	void Create(uint width, uint height, byte* pixels, uint bits);

	void Bind();
	void Unbind();

private:
	uint m_TextureID;
	uint m_Width;
	uint m_Height;
	uint m_Bits;
};

} }