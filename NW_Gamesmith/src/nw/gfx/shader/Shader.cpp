#include "Shader.h"
#include "DefaultShader.h"

#include <nw/math/Vector2.h>
#include <nw/math/Vector3.h>
#include <nw/math/Vector4.h>
#include <nw/math/Matrix4.h>

#include <iostream>
#include <vector>
#include <GL/glew.h>

using namespace nw;
using namespace gfx;
using namespace math;

Shader::~Shader()
{

}

void Shader::Bind()
{
	glUseProgram(m_ShaderID);
}

void Shader::SetUniformI(const std::string& name, int i) const
{
	glUniform1i(GetUniformLocationID(name), i);
}

void Shader::SetUniformF(const std::string& name, float f) const
{
	glUniform1f(GetUniformLocationID(name), f);
}

void Shader::SetUniformVec2(const std::string& name, const Vector2& vec) const
{

	glUniform2f(GetUniformLocationID(name), vec.x, vec.y);
}

void Shader::SetUniformVec3(const std::string& name, const Vector3& vec) const
{
	glUniform3f(GetUniformLocationID(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4(const std::string& name, const Vector4& vec) const
{
	glUniform4f(GetUniformLocationID(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat4(const std::string& name, const Matrix4& mat) const
{
	glUniformMatrix4fv(GetUniformLocationID(name), 1, GL_FALSE, mat.elements);
}


Shader* Shader::Create(Types type)
{
	uint programID = glCreateProgram();

	std::string name;
	const char* vert;
	const char* frag;
	switch (type)
	{
		case Types::Diffuse:
			vert = default_diffuse_vert.c_str();
			frag = default_diffuse_frag.c_str();
			name = "Diffuse";
			break;

		case Types::Texture:
			vert = default_simple_texture_vert.c_str();
			frag = default_simple_texture_frag.c_str();
			name = "Texture";
			break;
	}

	uint vertID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertID, 1, &vert, nullptr);
	glCompileShader(vertID);
	if (!CheckShader(vertID, name + ": Vertex Shader")) // TODO: Name based on type
	{
		glDeleteProgram(programID);
		return nullptr;
	}

	uint fragID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragID, 1, &frag, nullptr);
	glCompileShader(fragID);
	if (!CheckShader(fragID, name + ": Fragment Shader")) // TODO: Name based on type
	{
		glDeleteShader(vertID);
		glDeleteProgram(programID);
		return nullptr;
	}

	glAttachShader(programID, vertID);
	glAttachShader(programID, fragID);

	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vertID);
	glDeleteShader(fragID);

	return new Shader(programID);
}


uint Shader::GetUniformLocationID(const std::string& name) const
{
	return glGetUniformLocation(m_ShaderID, name.c_str());
}

bool Shader::CheckShader(uint shaderID, const std::string& name)
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
	std::cout << "[Shader] Failed to compile \"" << name << "\":" << std::endl;
	std::cout << &error[0] << std::endl;
	glDeleteShader(shaderID);

	return false;
}