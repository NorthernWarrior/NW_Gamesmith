#pragma once

#include <map>
#include "Texture2D.h"

namespace gamesmith { namespace graphics {

	class TextureManager2D
	{
	private:
		static std::map<std::string, Texture2D*> m_Textures;

	public:
		static Texture2D* get(const std::string& name);

		static Texture2D* add(const std::string& name, Texture2D* texture);
		static Texture2D* addFromFile(const std::string& name, const std::string& filename);

		static void init();
		static void clear();

	private:
		TextureManager2D() {}
		TextureManager2D(const TextureManager2D&) {}
	};

} }