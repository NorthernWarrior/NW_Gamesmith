#include "Keyboard.h"

namespace gamesmith { namespace input {

	Keyboard::KeyStateMap Keyboard::keyStates;

	bool Keyboard::getKey(int key)
	{		
		return (glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS);
	}

	bool Keyboard::getKeyDown(int key)
	{
		return (keyStates[(Keyboard::Key)key] == InputManager::KeyState::StateDown);
	}

	bool Keyboard::getKeyUp(int key)
	{
		return (keyStates[(Keyboard::Key)key] == InputManager::KeyState::StateUp);
	}

} }