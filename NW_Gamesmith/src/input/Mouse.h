#pragma once

#include "InputManager.h"

#include "../maths/vec2.h"

namespace gamesmith { namespace input {

	class Mouse
	{
		friend class graphics::Window;
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

		static inline void SetPosition(maths::vec2f pos)
		{
			glfwSetCursorPos(glfwGetCurrentContext(), pos.x, pos.y);
		}
		static inline maths::vec2f GetPosition()
		{
			double x = 0, y = 0;
			glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
			return maths::vec2f(static_cast<float>(x), static_cast<float>(y));
		}

		static bool GetButton(int mouseButton);
		static bool GetButtonDown(int mouseButton);
		static bool GetButtonUp(int mouseButton);

	private:
		typedef std::map<Button, InputManager::KeyState> MouseStateMap;
		static MouseStateMap mouseStates;
	};

} }