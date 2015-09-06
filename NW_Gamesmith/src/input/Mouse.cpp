#include "Mouse.h"

namespace gamesmith { namespace input {

	Mouse::MouseStateMap Mouse::mouseStates;

	bool Mouse::getButton(int mouseButton)
	{		
		return (glfwGetMouseButton(glfwGetCurrentContext(), mouseButton) == GLFW_PRESS);
	}

	bool Mouse::getButtonDown(int mouseButton)
	{
		return (mouseStates[(Mouse::Button)mouseButton] == InputManager::KeyState::StateDown);
	}

	bool Mouse::getButtonUp(int mouseButton)
	{
		return (mouseStates[(Mouse::Button)mouseButton] == InputManager::KeyState::StateUp);
	}

} }