#include "Texture2D.h"

#include <GL/glew.h>

#include "../utils/File.h"

namespace gamesmith { namespace graphics {

	Texture2D::Texture2D() :
		m_TextureID(0), m_Filename(""), m_Width(0), m_Height(0)
	{}

	Texture2D::Texture2D(const std::string & filename) :
		m_TextureID(0), m_Filename(""), m_Width(0), m_Height(0)
	{
		loadFromFile(filename);
	}

	Texture2D::~Texture2D()
	{
		if (m_TextureID > 0)
			glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::bind()
	{
		if (m_TextureID == 0)
			return;
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool Texture2D::loadFromFile(const std::string & filename)
	{
		if (!File::exists(filename))
		{
			// TODO: Log!
			std::cout << "[Texture2D] Failed to load image \"" << filename << "\"! File does not exist." << std::endl;
			return false;
		}

		m_Filename = filename;

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		BYTE* pixels = nullptr;

		// check the file signature and deduce its format
		fif = FreeImage_GetFileType(filename.c_str(), 0);
		// if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename.c_str());
		// if still unkown, return failure
		if (fif == FIF_UNKNOWN)
		{
			// TODO: Log!
			std::cout << "[Texture2D] Failed to load image \"" << filename << "\"! Unknown file format." << std::endl;
			return false;
		}

		// check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename.c_str());
		// if the image failed to load, return failure
		if (!dib)
		{
			// TODO: Log!
			std::cout << "[Texture2D] Failed to load image \"" << filename << "\"! This format cannot be read." << std::endl;
			return false;
		}

		// retrieve the image data
		pixels = FreeImage_GetBits(dib);
		m_Width = FreeImage_GetWidth(dib);
		m_Height = FreeImage_GetHeight(dib);
		m_Bits = FreeImage_GetBPP(dib);
		// if somehow one of these failed (they shouldn't), return failure
		if ((pixels == 0) || (m_Width == 0) || (m_Height == 0))
		{
			// TODO: Log!
			std::cout << "[Texture2D] Failed to load image \"" << filename << "\"! Couldn't retreive image data." << std::endl;
			return false;
		}

		if (m_Bits != 24 && m_Bits != 32)
		{
			// TODO: Log!
			std::cout << "[Texture2D] Failed to load image \"" << filename << "\"! Unsupported image bit-depth! (" << m_Bits << ")" << std::endl;
		}
		int internalFormat = (m_Bits == 32 ? GL_RGBA : GL_RGB);
		uint imageFormat = (m_Bits == 32 ? GL_BGRA : GL_BGR);

		/*for (int i)*/

		// generate an OpenGL texture ID for this image
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, imageFormat, GL_UNSIGNED_BYTE, pixels);

		// unload the data
		FreeImage_Unload(dib);

		return true;
	}

} }


