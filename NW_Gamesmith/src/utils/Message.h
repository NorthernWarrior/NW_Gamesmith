#pragma once

#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <assert.h>
#endif

namespace gamesmith
{
	class Message
	{
	public:
		static void Show(const std::string& text, const std::string& caption)
		{
			// TODO: Support for Linux and Mac
#ifdef _WIN32
			MessageBox(0, text.c_str(), caption.c_str(), MB_OK);
#else
#ifdef _DEBUG
			assert(false); // Message Box only works for Windows right now, sorry :(
#else
			std::cout << "[MESSAGE] " << caption << ": " << text << std::endl;
#endif
#endif
		}
	};
}