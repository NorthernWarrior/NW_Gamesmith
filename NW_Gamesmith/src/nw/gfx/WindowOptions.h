#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <nw/math/Vector2.h>

#include <string>

namespace nw { namespace gfx {

struct NW_API WindowOptions
{
	uint Width = 900;	// Width  in Pixels
	uint Height = 450;	// Height in Pixels
	std::string Title = "Northern Warrior Gamesmith";
	bool VSync = true;
	bool CanResize = false;
	bool KeepInitialAspectRatio = true; // Only applies when CanResize = true
	ushort Samples = 4;

	uint ScreenWidth = Width;		// Width in screen size
	uint ScreenHeight = Height;		// Height in screen size

	inline void SetSize(const math::Vector2 size) { Width = static_cast<uint>(size.x); Height = static_cast<uint>(size.y); }
};

} }