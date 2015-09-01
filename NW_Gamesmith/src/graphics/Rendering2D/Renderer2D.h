#pragma once

#include "../Shader/Shader.h"
#include "Renderable2D.h"

namespace gamesmith { namespace graphics {

	class Renderer2D
	{
	public:
		virtual ~Renderer2D() {}

		virtual void bind() {}
		virtual void submit(const Renderable2D& renderable) = 0;
		virtual void unbind() {}
		virtual void display() = 0;

	};

} }