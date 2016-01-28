#pragma once

#include <nw/Types.h>
#include <nw/gfx/WindowOptions.h>

#include <string>

struct GLFWwindow;

namespace nw { namespace gfx {

class Window
{
public:
	Window(WindowOptions& windowOptions);
	~Window();

	void Show();
	void Clear();
	void Update();
	void Close();

	bool IsClosed();

private:
	static void WindowResizeCallback(GLFWwindow* window, int width, int height);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	int* m_GlfwHandle;
	WindowOptions& m_Options;

	float m_InitialAspectRatio;
};

} 
}