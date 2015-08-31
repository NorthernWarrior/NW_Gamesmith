#pragma once

#include "../utils/typedefs.h"
#include "../maths/vec4.h"

namespace gamesmith { namespace graphics {
	
	class Color
	{
	public:
		static unsigned int fromRGBA(maths::vec4f color)
		{
			byte r = static_cast<byte>(color.r * 255);
			byte g = static_cast<byte>(color.g * 255);
			byte b = static_cast<byte>(color.b * 255);
			byte a = static_cast<byte>(color.a * 255);
			return ((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
		}
		static unsigned int fromRGBA(byte r, byte g, byte b, byte a)
		{
			return ((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
		}
	};

}}