#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <string>

namespace nw { namespace gfx {

struct NW_API WindowOptions
{
	uint Width = 900, Height = 450;
	std::string Title = "Northern Warrior Gamesmith";
	bool Vsync = true;
	bool CanResize = false;
	ushort Samples = 4;
};

} }