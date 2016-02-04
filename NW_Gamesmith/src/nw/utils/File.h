#pragma once

#include <nw/CommonMacros.h>
#include <nw/Log.h>

namespace nw { namespace utils {

class NW_API File
{
public:
	inline static std::string ReadFile(const std::string& filename)
	{
		FILE* file;
		fopen_s(&file, filename.c_str(), "rt");
		if (file == nullptr)
		{
			LOG_ERROR("[File] Failed to open: \"" + filename + "\"!")
			return "";
		}

		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

	inline static bool Exists(const std::string& filename)
	{
		FILE* file;
		fopen_s(&file, filename.c_str(), "r");
		return (file != nullptr);
	}


private:
	File() {}
	File(const File&) {}
	~File() {}
};

} }