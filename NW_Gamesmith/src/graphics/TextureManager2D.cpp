#include "TextureManager2D.h"

namespace gamesmith { namespace graphics {

	std::map<std::string, Texture2D*> TextureManager2D::m_Textures;

	Texture2D* TextureManager2D::get(const std::string& name)
	{
		if (m_Textures.empty())
		{
			// TODO: Log!
			std::cout << "[TextureManager2D] Textures are empty!" << std::endl;
			return nullptr;
		}
		return m_Textures[name];
	}

	Texture2D* TextureManager2D::add(const std::string& name, Texture2D* texture)
	{
		if (m_Textures.find(name) != m_Textures.end())
		{
			// TODO: Log!
			std::cout << "[TextureManager2D] A texture with the name \"" << name << "\" already exists!" << std::endl;
			return m_Textures[name];
		}

		m_Textures[name] = texture;

		return texture;
	}

	Texture2D * TextureManager2D::addFromFile(const std::string& name, const std::string& filename)
	{
		if (m_Textures.find(name) != m_Textures.end())
		{
			// TODO: Log!
			std::cout << "[TextureManager2D] A texture with the name \"" << name << "\" already exists!" << std::endl;
			return m_Textures[name];
		}

		Texture2D* tex = new Texture2D();
		if (!tex->loadFromFile(filename))
			return nullptr;

		m_Textures[name] = tex;

		return tex;
	}

	void TextureManager2D::init()
	{
#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
#endif
	}

	void TextureManager2D::clear()
	{
		for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
			delete it->second;

#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
#endif
	}

} }