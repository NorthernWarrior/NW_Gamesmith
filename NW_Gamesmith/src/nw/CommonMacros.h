#pragma once

#pragma warning (disable:4251) // To disable the Warnings about NW_API for InputManager, Mouse and Keyboard

#ifdef NW_GAMESMITH
#define NW_API __declspec(dllexport)
#else
#define NW_API __declspec(dllimport)
#endif

#define BIT(x) (1 << x)