#include "Keyboard.h"

#include <GLFW/glfw3.h>

namespace nw { namespace input {

	Keyboard::KeyStateMap Keyboard::m_KeyStates;

	bool Keyboard::GetKey(int key)
	{		
		return (glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS);
	}

	bool Keyboard::GetKeyDown(int key)
	{
		return (m_KeyStates[(Keyboard::Key)key] == InputManager::KeyState::StateDown);
	}

	bool Keyboard::GetKeyUp(int key)
	{
		return (m_KeyStates[(Keyboard::Key)key] == InputManager::KeyState::StateUp);
	}

} }