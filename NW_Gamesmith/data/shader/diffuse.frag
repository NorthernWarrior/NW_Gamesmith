#version 400 core

in VertexData
{
	vec4 position;
	vec4 color;
} vd_in;

uniform vec2 light_pos;

layout(location = 0) out vec4 color;

void main()
{
	float intensity = 1.0 / length(vd_in.position.xy - light_pos);
	color = vd_in.color * intensity;
}