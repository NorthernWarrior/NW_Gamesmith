#pragma once

#include <string>

///////////////////////////////////////////////////
// Diffuse
static const std::string default_diffuse_vert =
"#version 400 core \n"

"layout(location = 0) in vec4 position; \n"
"layout(location = 2) in vec4 color; \n"

"uniform mat4 pr_matrix; \n"

"out vec4 v_color; \n"

"void main() \n"
"{ \n"
"	gl_Position = pr_matrix * position; \n"
"\n"
"   // Flip the colors, so that they match this layout: ARGB when defined like 0xFF23CA11\n"
"	v_color = vec4(color.b, color.g, color.r, color.a); \n"
"}";

static const std::string default_diffuse_frag =
"#version 400 core \n"

"in vec4 v_color; \n"

"layout(location = 0) out vec4 color; \n"

"void main() { \n"
"	color = v_color; \n"
"}";

///////////////////////////////////////////////////
// Simple Texture
static const std::string default_simple_texture_vert =
"#version 400 core \n"

"layout(location = 0) in vec4 position; \n"
"layout(location = 1) in vec2 uv; \n"
"layout(location = 2) in vec4 color; \n"

"uniform mat4 pr_matrix; \n"

"out VertexData \n"
"{ \n"
"	vec4 position; \n"
"	vec2 uv; \n"
"	vec4 color; \n"
"} vd_out; \n"

"void main() \n"
"{ \n"
"	gl_Position = pr_matrix * position; \n"
"\n"
"   // Flip the colors, so that they match this layout: ARGB when defined like 0xFF23CA11\n"
"	vd_out.position = pr_matrix * position; \n"
"	vd_out.uv = uv; \n"
"	vd_out.color = vec4(color.b, color.g, color.r, color.a); \n"
"}";

static const std::string default_simple_texture_frag =
"#version 400 core \n"

"in VertexData \n"
"{ \n"
"	vec4 position; \n"
"	vec2 uv; \n"
"	vec4 color; \n"
"} vd_in; \n"

"uniform sampler2D tex; \n"

"layout(location = 0) out vec4 color; \n"

"void main() { \n"
"	color = vd_in.color; \n"
"	color = color * texture(tex, vd_in.uv); \n"
"}";