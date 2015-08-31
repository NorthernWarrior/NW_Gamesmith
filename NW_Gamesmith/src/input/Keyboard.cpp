#include "Keyboard.h"

namespace gamesmith { namespace input {

	Keyboard::KeyStateMap Keyboard::keyStates;

	bool Keyboard::GetKey(int key)
	{		
		return (glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS);
	}

	bool Keyboard::GetKeyDown(int key)
	{
		return (keyStates[(Keyboard::Key)key] == InputManager::KeyState::StateDown);
	}

	bool Keyboard::GetKeyUp(int key)
	{
		return (keyStates[(Keyboard::Key)key] == InputManager::KeyState::StateUp);
	}

} }