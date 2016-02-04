#pragma once

#include <nw/CommonMacros.h>

#include <string>
#include <map>

namespace nw { namespace rm {

class NW_API ResourceManager
{ 
public:
	template<class T>
	static T* Get(const std::string& name);

	template<class T>
	static T* LoadFromFile(const std::string& filename);
	template<class T>
	static T* LoadFromFile(const std::string& filename, const std::string& name);

private:
	typedef std::map<std::string, std::map<std::string, void*>> ResourceMap;
	static ResourceMap m_Resources;


private:
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	~ResourceManager() {}
};

} }