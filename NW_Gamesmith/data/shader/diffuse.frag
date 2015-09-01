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
	float distance = length(light_pos - vd_in.position.xy);
	float brightness = 40 / distance;
	brightness = clamp(brightness, 0.0, 2.0);

	color = vd_in.color * brightness;
	color.a = 1.0f;
}