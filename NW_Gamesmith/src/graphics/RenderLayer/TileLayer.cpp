#include "TileLayer.h"

namespace gamesmith { namespace graphics {

	TileLayer::TileLayer(Renderer2D * renderer, Shader* shader) :
		RenderLayer2D(renderer, shader)
	{
	}

	TileLayer::~TileLayer()
	{
		for (Renderable2D* r : m_Renderables)
			delete r;
	}

	Renderable2D * TileLayer::add(Renderable2D * renderable)
	{
		m_Renderables.push_back(renderable);
		return renderable;
	}

	void TileLayer::render()
	{
		m_Shader->bind();
		m_Renderer->bind();
		for (Renderable2D* r : m_Renderables)
			m_Renderer->submit(r);
		m_Renderer->unbind();

		m_Renderer->display();
	}

} }