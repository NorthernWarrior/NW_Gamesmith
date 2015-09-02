#pragma once

#include "../Rendering2D/Renderer2D.h"
#include "../Rendering2D/Renderable2D.h"

namespace gamesmith { namespace graphics {

	class RenderLayer2D
	{
	protected:
		Renderer2D* m_Renderer;
		Shader* m_Shader;

	public:
		RenderLayer2D(Renderer2D* renderer, Shader* shader) : m_Renderer(renderer), m_Shader(shader) {}
		virtual ~RenderLayer2D();

		virtual Renderable2D* add(Renderable2D* renderable) = 0;
		virtual void render() = 0;
	};

} }