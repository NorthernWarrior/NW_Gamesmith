#pragma once

#include <nw/CommonMacros.h>

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

private:
	gfx::Window* m_Window;
	int m_Result;
	
};

}