#include "Mouse.h"

namespace gamesmith { namespace input {

	Mouse::MouseStateMap Mouse::mouseStates;

	bool Mouse::GetButton(int mouseButton)
	{		
		return (glfwGetMouseButton(glfwGetCurrentContext(), mouseButton) == GLFW_PRESS);
	}

	bool Mouse::GetButtonDown(int mouseButton)
	{
		return (mouseStates[(Mouse::Button)mouseButton] == InputManager::KeyState::StateDown);
	}

	bool Mouse::GetButtonUp(int mouseButton)
	{
		return (mouseStates[(Mouse::Button)mouseButton] == InputManager::KeyState::StateUp);
	}

} }