#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <string>

namespace nw { namespace gfx {

struct NW_API WindowOptions
{
	uint Width = 900;	// Width in pixels
	uint Height = 450;	// Height in pixels
	std::string Title = "Northern Warrior Gamesmith";
	bool Vsync = true;
	bool CanResize = false;
	bool KeepInitialAspectRatio = true; // Only applies when CanResize = true
	ushort Samples = 4;

	uint ScreenWidth = Width;		// Width in screen size
	uint ScreenHeight = Height;		// Height in screen size
};

} }