#pragma once

#pragma warning (disable:4251) // To disable the Warnings about NW_API for InputManager, Mouse and Keyboard

#ifdef NW_GAMESMITH
#define NW_API __declspec(dllexport)
#else
#define NW_API __declspec(dllimport)
#endif

#define NW_BIT(x) (1 << x)

#define NW_FOR(start, end) for (int i = static_cast<int>(start); i < static_cast<int>(end); ++i)
#define NW_FOR_2D(width, height) int nw_width = static_cast<int>(width); int nw_height = static_cast<int>(height); for (int y = 0; y < nw_height; ++y) for (int x = 0; x < nw_width; ++x)