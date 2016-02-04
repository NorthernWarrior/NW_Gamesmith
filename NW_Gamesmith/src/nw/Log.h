#pragma once

#include <iostream>
#include <string>

namespace nw {namespace internal {
	
template <typename Arg>
static inline void _LogMessage(Arg&& arg)
{ 
	std::cout << arg << " ";
}

template <typename Arg, typename... Args>
static inline void _LogMessage(Arg&& arg, Args&&... args)
{
	std::cout << arg << " ";
	if (sizeof...(args))
		_LogMessage(std::forward<Args>(args)...);
}

template <typename... Args>
static inline void LogMessage(const std::string& prefix, Args&&... args)
{
	std::cout << prefix;
	_LogMessage(std::forward<Args>(args)...);
	std::cout << std::endl;
}

} }

#define LOG(...) nw::internal::LogMessage(std::string("Gamesmith >>"), __VA_ARGS__);

#define LOG_WARNING(...) nw::internal::LogMessage(std::string("Gamesmith Warning >>"), __VA_ARGS__);

#define LOG_ERROR(...) nw::internal::LogMessage(std::string("Gamesmith Error >>"), __VA_ARGS__);

#define LOG_FATAL(...) { nw::internal::LogMessage(std::string("Gamesmith FATAL ERROR >>"), __VA_ARGS__); \
						__debugbreak(); }
