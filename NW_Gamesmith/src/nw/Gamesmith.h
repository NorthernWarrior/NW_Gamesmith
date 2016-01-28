#pragma once

#include <nw/CommonMacros.h>
#include <nw/gfx/WindowOptions.h>

namespace nw {

	namespace gfx { class Window; }

class NW_API Gamesmith
{
public:
	~Gamesmith();

	int Start();
	void Quit();
	void Quit(int result);

protected:
	virtual void OnInitialise() {};
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;

private:

	void Init();
	void Update();

protected:
	gfx::WindowOptions m_WindowOptions;

private:
	gfx::Window* m_Window;
	int m_Result;
	
};

}