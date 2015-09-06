#version 400 core

in VertexData
{
	vec4 position;
	vec2 uv;
	vec4 color;
} vd_in;

uniform vec2 light_pos;
uniform sampler2D tex;

layout(location = 0) out vec4 color;

void main()
{
	float distance = length(light_pos - vd_in.position.xy);
	float brightness = 300 / distance;
	brightness = clamp(brightness, 0.0, 2.0);

	color = vd_in.color * brightness;
	color = color * texture(tex, vd_in.uv);
}