#pragma once

#include <functional>
#include <map>
#include <list>

#include "../graphics/Window.h"

namespace gamesmith { namespace input {

	class InputManager
	{
		friend class graphics::Window;
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

		static bool findButton(const std::string& name, std::function<bool(int)> keyFunc, std::function<bool(int)> mouseFunc);

		typedef std::map<std::string, std::list<int>> KeyNameMap;
		static KeyNameMap keyNames;

		typedef std::map<std::string, std::list<int>> MouseNameMap;
		static MouseNameMap mouseNames;
	};

} }