#pragma once

#include <iostream>
#include <string>
#include <FreeImage/FreeImage.h>
#include "../utils/typedefs.h"

namespace gamesmith { namespace graphics {

	class Texture2D
	{
	private:
		uint m_TextureID;
		std::string m_Filename;
		uint m_Width, m_Height;
		uint m_Bits;

	public: 
		Texture2D();
		Texture2D(const std::string& filename);
		~Texture2D();

		void bind();
		void unbind();

		bool loadFromFile(const std::string& filename);

	};

} }