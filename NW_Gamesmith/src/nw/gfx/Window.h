#pragma once

#include <nw/Types.h>

#include <string>

struct GLFWwindow;

namespace nw { namespace gfx {


class Window
{
public:
	Window();
	Window(uint width, uint height, const std::string& title);
	~Window();

	void Show();
	void Clear();
	void Update();
	void Close();

	bool IsClosed();

private:
	static void WindowResize(GLFWwindow* window, int width, int height);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	int* m_GlfwHandle;
	uint m_Width, m_Height;
	std::string m_Title;
	bool m_Vsync;
};

} 
}