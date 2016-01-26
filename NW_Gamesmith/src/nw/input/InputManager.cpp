#include "InputManager.h"

#include "Keyboard.h"
#include "Mouse.h"

namespace nw { namespace input {

	InputManager::KeyNameMap InputManager::m_KeyNames;
	InputManager::MouseNameMap InputManager::m_MouseNames;

	bool InputManager::GetButton(const std::string& name)
	{
		return FindButton(name, &Keyboard::GetKey, &Mouse::GetButton);
	}
	bool InputManager::GetButtonDown(const std::string& name)
	{
		return FindButton(name, &Keyboard::GetKeyDown, &Mouse::GetButtonDown);
	}
	bool InputManager::GetButtonUp(const std::string& name)
	{
		return FindButton(name, &Keyboard::GetKeyUp, &Mouse::GetButtonUp);
	}
		 
	void InputManager::RegisterButton(const std::string& name, int key)
	{
		m_KeyNames[name].push_back(key);
	}
	void InputManager::RegisterMouseButton(const std::string& name, int mouseButton)
	{
		m_MouseNames[name].push_back(mouseButton);
	}

	bool InputManager::FindButton(const std::string& name, std::function<bool(int)> keyFunc, std::function<bool(int)> mouseFunc)
	{
		auto it_keys = m_KeyNames.find(name);
		auto it_mouse = m_MouseNames.find(name);
		auto keys = (it_keys != m_KeyNames.end());
		auto mouse = (it_mouse != m_MouseNames.end());
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