#include "Window.h"

#include <nw/input/Mouse.h>
#include <nw/input/Keyboard.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace nw;
using namespace gfx;


Window::Window(WindowOptions& windowOptions) :
	m_GlfwHandle(nullptr)
	, m_Options(windowOptions)
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

	m_InitialAspectRatio = (float)m_Options.Height / (float)m_Options.Width;
	glfwWindowHint(GLFW_SAMPLES, m_Options.Samples);
	glfwWindowHint(GLFW_RESIZABLE, m_Options.CanResize);
	m_GlfwHandle = (int*)glfwCreateWindow(m_Options.Width, m_Options.Height, m_Options.Title.c_str(), nullptr, nullptr);	if (!m_GlfwHandle)
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
	glfwSetWindowSizeCallback((GLFWwindow*)m_GlfwHandle, WindowResizeCallback);
	glfwSetKeyCallback((GLFWwindow*)m_GlfwHandle, KeyCallback);
	glfwSetMouseButtonCallback((GLFWwindow*)m_GlfwHandle, MouseButtonCallback);
	glfwSwapInterval(m_Options.Vsync);

	glClearColor(30 / 255.f, 30 / 255.f, 30 / 255.f, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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





void Window::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	int px_width, px_height;
	glfwGetFramebufferSize(window, &px_width, &px_height);

	Window* win = (Window*)glfwGetWindowUserPointer(window);

	if (win->m_Options.KeepInitialAspectRatio)
	{
		int actualWidth = px_width;
		int actualHeight = px_height;
		float initAR = win->m_InitialAspectRatio;
		float currAR = static_cast<float>(px_height) / static_cast<float>(px_width);
		if (currAR < initAR)
			px_width = px_height / initAR;
		else
			px_height = px_width * initAR;
		glViewport((actualWidth - px_width) / 2, (actualHeight - px_height) / 2, px_width, px_height);
	}
	else
		glViewport(0, 0, px_width, px_height);

	if (win == nullptr)
		return;
	win->m_Options.Width = static_cast<uint>(px_width);
	win->m_Options.Height = static_cast<uint>(px_height);
	win->m_Options.ScreenWidth = width;
	win->m_Options.ScreenHeight = height;
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