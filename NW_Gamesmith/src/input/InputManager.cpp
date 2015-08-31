#include "InputManager.h"

#include "Keyboard.h"
#include "Mouse.h"

namespace gamesmith { namespace input {

	InputManager::KeyNameMap InputManager::keyNames;
	InputManager::MouseNameMap InputManager::mouseNames;

	bool InputManager::GetButton(const std::string& name)
	{
		return findButton(name, &Keyboard::GetKey, &Mouse::GetButton);
	}
	bool InputManager::GetButtonDown(const std::string& name)
	{
		return findButton(name, &Keyboard::GetKeyDown, &Mouse::GetButtonDown);
	}
	bool InputManager::GetButtonUp(const std::string& name)
	{
		return findButton(name, &Keyboard::GetKeyUp, &Mouse::GetButtonUp);
	}
		 
	void InputManager::RegisterButton(const std::string& name, int key)
	{
		keyNames[name].push_back(key);
	}
	void InputManager::RegisterMouseButton(const std::string& name, int mouseButton)
	{
		mouseNames[name].push_back(mouseButton);
	}

	bool InputManager::findButton(const std::string& name, std::function<bool(int)> keyFunc, std::function<bool(int)> mouseFunc)
	{
		auto it_keys = keyNames.find(name);
		auto it_mouse = mouseNames.find(name);
		auto keys = (it_keys != keyNames.end());
		auto mouse = (it_mouse != mouseNames.end());
		if (!keys && !mouse)
			return false;

		if (keys && keyFunc != nullptr)
		{
			for (auto it = it_keys->second.begin(); it != it_keys->second.end(); ++it)
			{
				if (keyFunc((*it)))
					return true;
			}
		}
		if (mouse && mouseFunc != nullptr)
		{
			for (auto it = it_mouse->second.begin(); it != it_mouse->second.end(); ++it)
			{
				if (mouseFunc((*it)))
					return true;
			}
		}

		return false;
	}



} }