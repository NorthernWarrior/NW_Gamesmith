#include "Mouse.h"

#include <nw/math/Vector2.h>

#include <GLFW/glfw3.h>

namespace nw { namespace input {

Mouse::MouseStateMap Mouse::m_MouseStates;

void Mouse::SetPosition(const math::Vector2& pos)
{
	glfwSetCursorPos(glfwGetCurrentContext(), pos.x, pos.y);
}
math::Vector2 Mouse::GetPosition()
{
	double x = 0, y = 0;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	return math::Vector2(static_cast<float>(x), static_cast<float>(y));
}


bool Mouse::GetButton(int mouseButton)
{		
	return (glfwGetMouseButton(glfwGetCurrentContext(), mouseButton) == GLFW_PRESS);
}

bool Mouse::GetButtonDown(int mouseButton)
{
	return (m_MouseStates[(Mouse::Button)mouseButton] == InputManager::KeyState::StateDown);
}

bool Mouse::GetButtonUp(int mouseButton)
{
	return (m_MouseStates[(Mouse::Button)mouseButton] == InputManager::KeyState::StateUp);
}

} }