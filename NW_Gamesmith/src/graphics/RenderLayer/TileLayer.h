#pragma once

#include <vector>

#include "RenderLayer2D.h"

namespace gamesmith { namespace graphics {

	class TileLayer : public RenderLayer2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;

	public:
		TileLayer(Renderer2D* renderer, Shader* shader);
		virtual ~TileLayer();

		Renderable2D* add(Renderable2D* renderable) override;
		void render() override;

		inline Renderable2D* getRenderable(unsigned int index) { return (index >= m_Renderables.size() ? nullptr : m_Renderables[index]); }
	};

} }