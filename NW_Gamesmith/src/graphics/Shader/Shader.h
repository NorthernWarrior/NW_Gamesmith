#pragma once

#include <iostream>

#include <GL/glew.h>

#include "../../utils/typedefs.h"
#include "../../maths/Maths.h"

namespace gamesmith { namespace graphics {

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_COLOR_INDEX 2

	class Shader
	{
	private:
		uint m_ShaderID;
		std::string m_Vertex, m_Fragment;
		bool m_SourceIsString;

		static uint m_CurrentShader;

	public: 
		enum Default
		{
			Diffuse,
			SimpleTexture
		};

		~Shader();

		void bind() const;
		void unbind() const;

		void reload();

		void SetUniformI(const std::string& name, int i) const;
		void SetUniformF(const std::string& name, float f) const;
		void SetUniformVec2(const std::string& name, const maths::vec2f& vec) const;
		void SetUniformVec3(const std::string& name, const maths::vec3f& vec) const;
		void SetUniformVec4(const std::string& name, const maths::vec4f& vec) const;
		void SetUniformMat4(const std::string& name, const maths::mat4& mat) const;

		static Shader* create(const std::string& vertFile, const std::string& fragFile);
		static Shader* createFromString(const std::string& vertString, const std::string& fragString);

	private:
		Shader(uint programID, const std::string& vertFile, const std::string& fragFile, bool fromString) : 
			m_ShaderID(programID), m_Vertex(vertFile), m_Fragment(fragFile), m_SourceIsString(fromString) { }

		Shader(const Shader&) {}

		inline const uint getUniformLocationID(const std::string& name) const { return glGetUniformLocation(m_ShaderID, name.c_str()); }

		static bool checkShader(uint shaderID, const std::string& filename);
	};

} }