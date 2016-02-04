#include "ResourceManager.h"

#include <nw/gfx/Texture2D.h>
#include <nw/utils/File.h>

#include <FreeImage/FreeImage.h>

using namespace nw;
using namespace gfx;
using namespace rm;
using namespace utils;

#define RES_TYPE "Texture2D"

template<>
Texture2D* ResourceManager::Get<Texture2D>(const std::string& name)
{
	return (Texture2D*)m_Resources[RES_TYPE][name];
}
template NW_API Texture2D* ResourceManager::Get<Texture2D>(const std::string& name);



template<>
Texture2D* ResourceManager::LoadFromFile<Texture2D>(const std::string& filename, const std::string& name)
{
	if (!File::Exists(filename))
	{
		LOG_ERROR("[ResourceManager] Failed to load image \"" + filename + "\"! File does not exist.")
			return nullptr;
	}

	// TODO: only for now...
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr;
	BYTE* pixels = nullptr;
	uint width = 0;
	uint height = 0;
	uint bits = 0;

	// check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename.c_str(), 0);
	// if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	// if still unkown, return failure
	if (fif == FIF_UNKNOWN)
	{
		LOG_ERROR("[ResourceManager] Failed to load image \"" + filename + "\"! Unknown file format.")
			return nullptr;
	}

	// check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename.c_str());
	// if the image failed to load, return failure
	if (!dib)
	{
		LOG_ERROR("[ResourceManager] Failed to load image \"" + filename + "\"! This format cannot be read.")
			return nullptr;
	}

	// retrieve the image data
	pixels = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	bits = FreeImage_GetBPP(dib);

	// if somehow one of these failed (they shouldn't), return failure
	if ((pixels == 0) || (width == 0) || (height == 0))
	{
		LOG_ERROR("[ResourceManager] Failed to load image \"" + filename + "\"! Couldn't retreive image data.");
		return false;
	}

	Texture2D* texture = Texture2D::Create(width, height, bits, pixels);

	// unload the data
	FreeImage_Unload(dib);

	// TODO: only for now...
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif

	if (texture != nullptr)
		m_Resources[RES_TYPE][name] = texture;

	return texture;
}
template<>
Texture2D* ResourceManager::LoadFromFile<Texture2D>(const std::string& filename)
{
	return LoadFromFile<Texture2D>(filename, filename);
}
template NW_API Texture2D* ResourceManager::LoadFromFile<Texture2D>(const std::string& filename);
template NW_API Texture2D* ResourceManager::LoadFromFile<Texture2D>(const std::string& filename, const std::string& name);