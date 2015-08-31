#pragma once

#include "InputManager.h"

namespace gamesmith { namespace input {

	class Keyboard
	{
		friend class graphics::Window;
		friend class InputManager;

	public:
		enum Key
		{
			Space = 32,
			Apostrophe = 39,		/* ' */
			Comma = 44,				/* , */
			Minus = 45,				/* - */
			Period = 46,			/* . */
			Slash = 47,				/* / */
			Semicolon = 59,			/* ; */
			Equal = 61,				/* = */
			BracketLeft = 91,		/* [ */
			Backslash = 92,			/* \ */
			BracketRight = 93,		/* ] */
			AccentGrave = 96,		/* ` */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,

			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,

			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			Menu = 348,

			ShiftLeft = 340,
			ShiftRight = 344,
			ControlLeft = 341,
			ControlRight = 345,
			AltLeft = 342,
			AltRight = 346,
			SuperLeft = 343,
			SuperRight = 347,

			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			Num0 = 48,
			Num1 = 49,
			Num2 = 50,
			Num3 = 51,
			Num4 = 52,
			Num5 = 53,
			Num6 = 54,
			Num7 = 55,
			Num8 = 56,
			Num9 = 57,

			NumPad0 = 320,
			NumPad1 = 321,
			NumPad2 = 322,
			NumPad3 = 323,
			NumPad4 = 324,
			NumPad5 = 325,
			NumPad6 = 326,
			NumPad7 = 327,
			NumPad8 = 328,
			NumPad9 = 329,
			NumPadDecimal = 330,
			NumPadDivide = 331,
			NumPadMultiply = 332,
			NumPadSubtract = 333,
			NumPadAdd = 334,
			NumPadEnter = 335,
			NumPadEqual = 336,

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90
		};

		static bool GetKey(int key);
		static bool GetKeyDown(int key);
		static bool GetKeyUp(int key);

	private:
		typedef std::map<Key, InputManager::KeyState> KeyStateMap;
		static KeyStateMap keyStates;
	};

} }