#include "Window.h"

#include <nw/input/Mouse.h>
#include <nw/input/Keyboard.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace nw;
using namespace gfx;


Window::Window() :
	m_GlfwHandle(nullptr)
	, m_Width(900)
	, m_Height(450)
	, m_Title("Northern Warrior Gamesmith")
	, m_Vsync(false)
{
}

Window::Window(uint width, uint height, const std::string& title) :
	m_GlfwHandle(nullptr)
	, m_Width(width)
	, m_Height(height)
	, m_Title(title)
	, m_Vsync(true)
{
}

Window::~Window()
{
	if (m_GlfwHandle != nullptr)
		glfwDestroyWindow((GLFWwindow*)m_GlfwHandle);

	glfwTerminate();
}



void Window::Show()
{
	if (!glfwInit())
	{
		// TODO: Log!
		std::cout << "[Window] Failed to initialize GLFW!" << std::endl;
		return;
	}

	m_GlfwHandle = (int*)glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (!m_GlfwHandle)
	{
		// TODO: Log!
		std::cout << "[Window] Failed to create Window!" << std::endl;
		return;
	}
	glfwMakeContextCurrent((GLFWwindow*)m_GlfwHandle);
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow((GLFWwindow*)m_GlfwHandle);
		m_GlfwHandle = nullptr;
		// TODO: Log!
		std::cout << "[Window] Failed to initialize GLEW!";
		return;
	}
	glfwSetWindowUserPointer((GLFWwindow*)m_GlfwHandle, this);
	glfwSetWindowSizeCallback((GLFWwindow*)m_GlfwHandle, WindowResize);
	glfwSetKeyCallback((GLFWwindow*)m_GlfwHandle, KeyCallback);
	glfwSetMouseButtonCallback((GLFWwindow*)m_GlfwHandle, MouseButtonCallback);
	glfwSwapInterval(m_Vsync);

	glClearColor(30 / 255.f, 30 / 255.f, 30 / 255.f, 1.0f);

	// TODO: Log!
#ifdef _DEBUG
	std::cout << "[Window] Running in Debug Mode!" << std::endl;
#endif
	std::cout << "[Window] OpenGL Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "[Window] OpenGL Version:  " << glGetString(GL_VERSION) << std::endl;
	std::cout << "[Window] OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	glfwSwapBuffers((GLFWwindow*)m_GlfwHandle);
	input::Keyboard::m_KeyStates.clear();
	input::Mouse::m_MouseStates.clear();
	glfwPollEvents();
}

void Window::Close()
{
	glfwSetWindowShouldClose((GLFWwindow*)m_GlfwHandle, GL_TRUE);
}



bool Window::IsClosed()
{	
	return (glfwWindowShouldClose((GLFWwindow*)m_GlfwHandle) > 0);
}





void Window::WindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	if (win == nullptr)
		return;
	win->m_Width = (uint)width;
	win->m_Height = (uint)height;
}
void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto k = (input::Keyboard::Key)key;

	switch (action)
	{
		case GLFW_PRESS:
			input::Keyboard::m_KeyStates[k] = input::InputManager::KeyState::StateDown;
			break;

		case GLFW_RELEASE:
			input::Keyboard::m_KeyStates[k] = input::InputManager::KeyState::StateUp;
			break;
	}
}
void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	auto m = (input::Mouse::Button)button;

	switch (action)
	{
		case GLFW_PRESS:
			input::Mouse::m_MouseStates[m] = input::InputManager::KeyState::StateDown;
			break;

		case GLFW_RELEASE:
			input::Mouse::m_MouseStates[m] = input::InputManager::KeyState::StateUp;
			break;
	}
}