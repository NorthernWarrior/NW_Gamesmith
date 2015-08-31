#pragma once

#include <string>

namespace gamesmith
{
	class File
	{
	public:
		inline static std::string readFile(const std::string& filename)
		{
			FILE* file;
			fopen_s(&file, filename.c_str(), "rt");
			if (file == nullptr)
			{
				// TODO: Log!
				std::cout << "[File] Failed to open: \"" << filename << "\"!" << std::endl;
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


	private:
		File() {}
		File(const File&) {}
		~File() {}
	};
}