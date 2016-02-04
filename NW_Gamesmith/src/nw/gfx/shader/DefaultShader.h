#pragma once

#include <string>

///////////////////////////////////////////////////
// Diffuse
static const std::string default_diffuse_vert =
"#version 400 core \n"

"layout(location = 0) in vec4 position; \n"
"layout(location = 2) in vec4 color; \n"

"uniform mat4 projection_matrix; \n"

"out vec4 v_color; \n"

"void main() \n"
"{ \n"
"	gl_Position = projection_matrix * position; \n"
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
"layout(location = 3) in float texID; \n"

"uniform mat4 projection_matrix; \n"
"uniform mat4 view_matrix; \n"

"out VertexData \n"
"{ \n"
"	vec4 position; \n"
"	vec2 uv; \n"
"	vec4 color; \n"
"   float tid; \n"
"} vd_out; \n"

"void main() \n"
"{ \n"
"	gl_Position = projection_matrix * view_matrix * position; \n"
"\n"
"   // Flip the colors, so that they match this layout: ARGB when defined like 0xFF23CA11\n"
"	vd_out.position = projection_matrix * position; \n"
"	vd_out.uv = uv; \n"
"	vd_out.color = vec4(color.b, color.g, color.r, color.a); \n"
"   vd_out.tid = texID; \n"
"}";

static const std::string default_simple_texture_frag =
"#version 400 core \n"

"in VertexData \n"
"{ \n"
"	vec4 position; \n"
"	vec2 uv; \n"
"	vec4 color; \n"
"   float tid; \n"
"} vd_in; \n"

"uniform sampler2D tex[32]; \n"

"layout(location = 0) out vec4 color; \n"

"void main() { \n"
"	vec4 texColor = vd_in.color; \n"
"   if (vd_in.tid > 0.0) \n"
"   { \n"
"		int tid = int(vd_in.tid - 0.5); \n"
"		texColor = texture(tex[tid], vd_in.uv); \n"
"   } \n"
"	color = texColor; \n"
"}";