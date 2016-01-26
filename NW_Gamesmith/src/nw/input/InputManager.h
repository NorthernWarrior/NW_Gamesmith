#pragma once

#include <nw/CommonMacros.h>

#include <functional>
#include <map>
#include <list>

namespace nw { namespace gfx { class Window; } }

namespace nw { namespace input {


	class NW_API InputManager
	{
		friend class nw::gfx::Window;
		friend class Keyboard;
		friend class Mouse;

	public:
		static bool GetButton(const std::string& name);
		static bool GetButtonDown(const std::string& name);
		static bool GetButtonUp(const std::string& name);  

		static void RegisterButton(const std::string& name, int key);
		static void RegisterMouseButton(const std::string& name, int mouseButton);

	private:
		enum KeyState
		{
			None,
			StateDown,
			StateUp
		};

		static bool FindButton(const std::string& name, std::function<bool(int)> keyFunc, std::function<bool(int)> mouseFunc);

		typedef std::map<std::string, std::list<int>> KeyNameMap;
		static KeyNameMap m_KeyNames;

		typedef std::map<std::string, std::list<int>> MouseNameMap;
		static MouseNameMap m_MouseNames;
	};

} }