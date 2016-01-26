#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

namespace nw { namespace gfx {

class NW_API IndexBuffer 
{
public:
	IndexBuffer(const uint* indices, uint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline uint GetCount() const { return m_Count; }

private:
	uint m_ID;
	uint m_Count;

};

} }