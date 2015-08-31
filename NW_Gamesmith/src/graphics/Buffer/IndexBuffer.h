#pragma once

#include "../../utils/typedefs.h"

namespace gamesmith { namespace graphics {

	class IndexBuffer
	{
	private:
		uint m_ID;
		uint m_Count;

	public:
		IndexBuffer(const ushort* indices, uint count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline uint getCount() const { return m_Count; }
	};

} }