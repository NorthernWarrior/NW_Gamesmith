#pragma once

#include <string>

namespace gamesmith
{
	class Message
	{
	public:
		static void Show(const std::string& text, const std::string& caption);
	};
}