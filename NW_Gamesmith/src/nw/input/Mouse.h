#pragma once

#include <nw/input/InputManager.h>
#include <nw/Types.h>

namespace nw { namespace input {

	class NW_API Mouse
	{
		friend class nw::gfx::Window;
		friend class InputManager;

	public:
		enum Button
		{
			Button1 = 0,
			Button2 = 1,
			Button3 = 2,
			Button4 = 3,
			Button5 = 4,
			Button6 = 5,
			Button7 = 6,
			Button8 = 7,
			ButtonLeft = Button1,
			ButtonRight = Button2,
			ButtonMiddle = Button3
		};

		static void SetPosition(const math::Vector2& pos);
		static math::Vector2 GetPosition();

		static bool GetButton(int mouseButton);
		static bool GetButtonDown(int mouseButton);
		static bool GetButtonUp(int mouseButton);

	private:
		typedef std::map<Button, InputManager::KeyState> MouseStateMap;
		static MouseStateMap m_MouseStates;
	};

} }