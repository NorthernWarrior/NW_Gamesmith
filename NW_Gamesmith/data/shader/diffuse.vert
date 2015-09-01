#version 400 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

uniform vec2 light_pos;

out VertexData
{
	vec4 position;
	vec4 color;
} vd_out;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;

	vd_out.position = pr_matrix * position;
	vd_out.color = color;
}