#pragma once

#include <nw/CommonMacros.h>
#include <nw/Types.h>

#include <string>

namespace nw { namespace gfx { 

class NW_API Shader
{
public:
	enum Types
	{
		Diffuse,
		Texture,
	};

public:
	~Shader();

	void Bind();

	void SetUniformI(const std::string& name, int i) const;
	void SetUniformI(const std::string& name, int* i, int cnt) const;
	void SetUniformF(const std::string& name, float f) const;
	void SetUniformVec2(const std::string& name, const math::Vector2& vec) const;
	void SetUniformVec3(const std::string& name, const math::Vector3& vec) const;
	void SetUniformVec4(const std::string& name, const math::Vector4& vec) const;
	void SetUniformMat4(const std::string& name, const math::Matrix4& mat) const;

	static Shader* Create(Types type);

private:
	Shader(uint programID) :
		m_ShaderID(programID)
	{}

	Shader(const Shader& copy) {}

	uint GetUniformLocationID(const std::string& name) const;

	static bool CheckShader(uint shaderID, const std::string& name);

private:
	uint m_ShaderID;
};

} }