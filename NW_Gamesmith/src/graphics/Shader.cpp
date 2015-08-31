#include "Shader.h"

#include <vector>

#include "../utils/File.h"

namespace gamesmith { namespace graphics {
	
	uint Shader::m_CurrentShader = 0;

	Shader::~Shader()
	{
		// TODO: Some kind of Management, to only delete program if no other shader uses it!
		//if (m_ShaderID > 0)
			//glDeleteProgram(m_ShaderID);
	}

	void Shader::bind() const
	{
		m_CurrentShader = m_ShaderID;
		glUseProgram(m_ShaderID);
	}

	void Shader::unbind() const
	{
		if (m_CurrentShader == 0 || m_CurrentShader == m_ShaderID)
			glUseProgram(0);
	}

	void Shader::reload()
	{
		Shader* newShader = create(m_VertFile, m_FragFile);
		if (newShader == nullptr || newShader->m_ShaderID == 0)
		{
			// TODO: Log!
			std::cout << "[Shader] Failed to reload the shader! Keeping old one active." << std::endl;
			return;
		}

		if (m_ShaderID > 0)
			glDeleteProgram(m_ShaderID);

		m_ShaderID = newShader->m_ShaderID;
		delete newShader;
	}

	void Shader::SetUniformI(const std::string& name, int i) const
	{
		if (m_CurrentShader != m_ShaderID)
			bind();
		glUniform1i(getUniformLocationID(name), i);
	}

	void Shader::SetUniformF(const std::string& name, float f) const
	{
		if (m_CurrentShader != m_ShaderID)
			bind();
		glUniform1f(getUniformLocationID(name), f);
	}

	void Shader::SetUniformVec2(const std::string& name, const maths::vec2f & vec) const
	{
		if (m_CurrentShader != m_ShaderID)
			bind();
		glUniform2f(getUniformLocationID(name), vec.x, vec.y);
	}

	void Shader::SetUniformVec3(const std::string& name, const maths::vec3f & vec) const
	{
		if (m_CurrentShader != m_ShaderID)
			bind();
		glUniform3f(getUniformLocationID(name), vec.x, vec.y, vec.z);
	}

	void Shader::SetUniformVec4(const std::string& name, const maths::vec4f & vec) const
	{
		if (m_CurrentShader != m_ShaderID)
			bind();
		glUniform4f(getUniformLocationID(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::SetUniformMat4(const std::string& name, const maths::mat4& mat) const
	{
		if (m_CurrentShader != m_ShaderID)
			bind();
		glUniformMatrix4fv(getUniformLocationID(name), 1, GL_FALSE,	mat.elements);
	}

	Shader* Shader::create(const std::string & vertFile, const std::string & fragFile)
	{
		uint program = glCreateProgram();

		std::string& vertString = File::readFile(vertFile);
		const char* vert = vertString.c_str();
		uint vertID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertID, 1, &vert, nullptr);
		glCompileShader(vertID);
		if (!checkShader(vertID, vertFile))
		{
			glDeleteProgram(program);
			return nullptr;
		}

		std::string& fragString = File::readFile(fragFile);
		const char* frag = fragString.c_str();
		uint fragID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragID, 1, &frag, nullptr);
		glCompileShader(fragID);
		if (!checkShader(fragID, fragFile))
		{
			glDeleteShader(vertID);
			glDeleteProgram(program);
			return nullptr;
		}

		glAttachShader(program, vertID);
		glAttachShader(program, fragID);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertID);
		glDeleteShader(fragID);

		return new Shader(program, vertFile, fragFile);
	}

	bool Shader::checkShader(uint shaderID, const std::string& filename)
	{
		int result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_TRUE)
			return true;

		GLint length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length + 1);
		glGetShaderInfoLog(shaderID, length, nullptr, &error[0]);
		// TODO: Log!
		std::cout << "[Shader] Failed to compile \"" << filename << "\":" << std::endl;
		std::cout << &error[0] << std::endl;
		glDeleteShader(shaderID);

		return false;
	}

} }