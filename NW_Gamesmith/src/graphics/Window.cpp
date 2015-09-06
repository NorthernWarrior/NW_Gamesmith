#include "Window.h"

#include "../input/Input.h"
#include "Shader/ShaderManager.h"
#include "TextureManager2D.h"

namespace gamesmith { namespace graphics {

	Window::Window() :
		m_GlfwHandle(nullptr), m_Vsync(false), m_Samples(0), m_Background(maths::vec3f(57.f / 255, 55.f / 255, 54.f / 255))
	{
		glfw_Init();
	}

	Window::Window(const std::string & title, int width, int height) :
		m_GlfwHandle(nullptr), m_Vsync(false), m_Samples(0), m_Background(maths::vec3f(57.f / 255, 55.f / 255, 54.f / 255))
	{
		glfw_Init();

		create(title, width, height);
	}

	Window::~Window()
	{
		ShaderManager::clear();
		TextureManager2D::clear();

		if (m_GlfwHandle != nullptr)
			glfwDestroyWindow(m_GlfwHandle);

		glfwTerminate();
	}

	bool Window::create(const std::string & title, int width, int height)
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;

		glfwWindowHint(GLFW_SAMPLES, m_Samples);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_GlfwHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!m_GlfwHandle)
		{
			// TODO: Log!
			std::cout << "[Window] Failed to create Window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_GlfwHandle);
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			m_GlfwHandle = nullptr;
			// TODO: Log!
			std::cout << "[Window] Failed to initialize GLEW!";
			return false;
		}
		glfwSetWindowUserPointer(m_GlfwHandle, this);
		glfwSetWindowSizeCallback(m_GlfwHandle, Window::windowResize);
		glfwSetKeyCallback(m_GlfwHandle, Window::keyCallback);
		glfwSetMouseButtonCallback(m_GlfwHandle, Window::mouseButtonCallback);

		setVsync(m_Vsync);

		glClearColor(m_Background.r, m_Background.g, m_Background.b, 1.0f); 

		// TODO: Log!
		std::cout << "[Window] OpenGL: " << glGetString(GL_VERSION) << std::endl;

		ShaderManager::loadDefault();
		TextureManager2D::init();
		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() const
	{
		glfwSwapBuffers(m_GlfwHandle);
		input::Keyboard::keyStates.clear();
		input::Mouse::mouseStates.clear();
		glfwPollEvents();
	}

	void Window::setSamples(ushort samples)
	{
		m_Samples = samples;
		// TODO: Window recreation!
	}

	void Window::setVsync(bool enabled)
	{
		m_Vsync = enabled;
		glfwSwapInterval(m_Vsync);
	}

	void Window::setBackground(maths::vec3f color)
	{
		m_Background = color;
		glClearColor(m_Background.r, m_Background.g, m_Background.b, 1.0f);
	}

	void Window::glfw_Init()
	{
		if (!glfwInit())
		{
			// TODO: Log!
			std::cout << "[Window] Failed to initialize GLFW!" << std::endl;
			return;
		}
	}


	void Window::windowResize(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (win == nullptr)
			return;
		win->m_Width = width;
		win->m_Height = height;
	}	
	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto k = (input::Keyboard::Key)key;

		switch (action)
		{
		case GLFW_PRESS:
			input::Keyboard::keyStates[k] = input::InputManager::KeyState::StateDown;
			break;

		case GLFW_RELEASE:
			input::Keyboard::keyStates[k] = input::InputManager::KeyState::StateUp;
			break;
		}
	}	
	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		auto m = (input::Mouse::Button)button;

		switch (action)
		{
		case GLFW_PRESS:
			input::Mouse::mouseStates[m] = input::InputManager::KeyState::StateDown;
			break;

		case GLFW_RELEASE:
			input::Mouse::mouseStates[m] = input::InputManager::KeyState::StateUp;

			break;
		}
	}

} }