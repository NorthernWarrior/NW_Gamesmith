#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/typedefs.h"
#include "../maths/Maths.h"

namespace gamesmith { namespace graphics {

	class Window
	{
	private:
		GLFWwindow* m_GlfwHandle;
		std::string m_Title;
		int m_Width, m_Height;
		bool m_Vsync;
		ushort m_Samples;
		maths::vec3f m_Background;

	public:
		Window();
		Window(const std::string& title, int width, int height);
		~Window();

		bool create(const std::string& title, int width, int height);
		void clear() const;
		void update() const;
		inline const bool run() const { update(); clear(); return !isClosed(); }

		void setSamples(ushort samples);
		void setVsync(bool enabled);
		void setBackground(maths::vec3f color);

		inline uint getWidth() const { return m_Width; }
		inline uint getHeight() const { return m_Height; }
		inline bool isClosed() const { return (m_GlfwHandle != nullptr ? (glfwWindowShouldClose(m_GlfwHandle) > 0) : true); }
		inline bool isVsyncEnabled() const{ return m_Vsync; }

	private:
		static void windowResize(GLFWwindow* window, int width, int height);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	private:
		void glfw_Init();
	};

} }