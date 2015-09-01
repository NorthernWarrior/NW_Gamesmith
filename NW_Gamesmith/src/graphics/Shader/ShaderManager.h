#pragma once

#include "Shader.h"

#include <map>

namespace gamesmith { namespace graphics {

	class ShaderManager
	{
	private:
		static std::map<Shader::Default, Shader*> m_DefaultShader;
		static std::map<std::string, Shader*> m_CustomShader;

	public:
		static Shader* get(Shader::Default shaderID);
		static Shader* get(const std::string& name);

		static Shader* loadFromFile(const std::string& name, const std::string& vertFile, const std::string& fragFile);
		static Shader* loadFromString(const std::string& name, const std::string& vertString, const std::string& fragString);

		static void loadDefault();
		static void clear();
	};

} }