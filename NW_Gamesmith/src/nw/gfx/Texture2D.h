#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <nw/math/Vector2.h>

namespace nw { namespace gfx {

class NW_API Texture2D
{
public:
	static Texture2D* Create(uint width, uint height, uint bits, byte* pixels);

	void Bind() const;
	void Unbind() const;

	inline math::Vector2 GetSize() const { return math::Vector2(static_cast<float>(m_Width), static_cast<float>(m_Height)); }
	inline uint GetID() const { return m_TextureID; }

private:
	Texture2D();
	~Texture2D();

private:
	uint m_TextureID;
	uint m_Width;
	uint m_Height;
	uint m_Bits;
};

} }