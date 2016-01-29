#include <Gamesmith.h>

#include <nw/gfx/Window.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace nw;
using namespace gfx;

Gamesmith::~Gamesmith()
{
	delete m_Window;
}

int Gamesmith::Start()
{
	Init();

	float bla = 1.f;
	int f = 0;
	double dt, begin = glfwGetTime();
	while (!m_Window->IsClosed())
	{
		dt = glfwGetTime() - begin;
		Time::m_DeltaTime = static_cast<float>(dt);
		begin = glfwGetTime();
		bla += dt;

		m_Window->Clear();

		Update();

		OnRender();

		m_Window->Update();

		++f;
		if (bla > 1)
		{
			std::cout << f << " fps    -  " << dt << " ms" << std::endl;
			bla -= 1.f;
			f = 0;
		}
	}

	return m_Result;
}

void Gamesmith::Quit()
{
	Quit(EXIT_SUCCESS);
}
void Gamesmith::Quit(int result)
{
	m_Window->Close();
}


void Gamesmith::Init()
{
	m_Result = EXIT_SUCCESS;

	m_Window = new Window;
	m_Window->Show();

	OnInitialise();
}



void Gamesmith::Update()
{
	OnUpdate();
}



// Variable definition for Time
float Time::m_DeltaTime = 0.0f;
float Time::m_TimeScale = 1.0f;