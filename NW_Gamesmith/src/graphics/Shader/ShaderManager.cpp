#include "ShaderManager.h"

#include <string>

#include "DefaultShader.h"

namespace gamesmith { namespace graphics {

	std::map<Shader::Default, Shader*> ShaderManager::m_DefaultShader;
	std::map<std::string, Shader*> ShaderManager::m_CustomShader;

	Shader * ShaderManager::get(Shader::Default shaderID)
	{
		if (m_DefaultShader.size() == 0)
		{
			// TODO: Log!
			std::cout << "[ShaderManager] Default shader are empty!" << std::endl;
			return nullptr;
		}
		return m_DefaultShader[shaderID];
	}

	Shader* ShaderManager::get(const std::string & name)
	{
		auto result = m_CustomShader.find(name);
		if (result == m_CustomShader.end())
		{
			// TODO: Log!
			std::cout << "[ShaderManager] Couldn't get a shader with the name \"" << name << "\"!" << std::endl;
			return nullptr;
		}
		return result->second;
	}

	Shader* ShaderManager::addFromFile(const std::string & name, const std::string & vertFile, const std::string & fragFile)
	{
		if (m_CustomShader.find(name) != m_CustomShader.end())
		{
			// TODO: Log!
			std::cout << "[ShaderManager] A shader with the name \"" << name << "\" already exists!" << std::endl;
			return m_CustomShader[name];
		}

		Shader* s = Shader::create(vertFile, fragFile);
		if (s == nullptr)
			return nullptr;

		m_CustomShader[name] = s;

		return s;
	}

	Shader* ShaderManager::addFromString(const std::string & name, const std::string & vertString, const std::string & fragString)
	{
		if (m_CustomShader.find(name) != m_CustomShader.end())
		{
			// TODO: Log!
			std::cout << "[ShaderManager] A shader with the name \"" << name << "\" already exists!" << std::endl;
			return m_CustomShader[name];
		}

		Shader* s = Shader::createFromString(vertString, fragString);
		if (s == nullptr)
			return nullptr;

		m_CustomShader[name] = s;

		return s;
	}

	void ShaderManager::loadDefault()
	{
		m_DefaultShader[Shader::Diffuse] = Shader::createFromString(default_diffuse_vert, default_diffuse_frag);
	}

	void ShaderManager::clear()
	{
		for (auto it = m_DefaultShader.begin(); it != m_DefaultShader.end(); ++it)
			delete it->second;

		for (auto it = m_CustomShader.begin(); it != m_CustomShader.end(); ++it)
			delete it->second;
	}

} }