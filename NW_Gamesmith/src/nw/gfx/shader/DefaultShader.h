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
"	v_color = color; \n"
"}";

static const std::string default_diffuse_frag =
"#version 400 core \n"

"in vec4 v_color; \n"

"layout(location = 0) out vec4 color; \n"

"void main() { \n"
"	color = v_color; \n"
"}";
