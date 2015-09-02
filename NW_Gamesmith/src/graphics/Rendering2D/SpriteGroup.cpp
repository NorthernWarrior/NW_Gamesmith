#include "SpriteGroup.h"

namespace gamesmith { namespace graphics {

	SpriteGroup::SpriteGroup(maths::vec2f position) 
	{
		m_Transform = Transform2D(position, 0, maths::vec2f(1, 1));
		m_Color = 0x00000000;
	}

	SpriteGroup::~SpriteGroup()
	{
		for (Renderable2D* r : m_Renderables)
			delete r;
	}

	Renderable2D * SpriteGroup::add(Renderable2D * renderable)
	{
		m_Renderables.push_back(renderable);
		return renderable;
	}

	void SpriteGroup::onSubmit(Renderer2D * renderer) const
	{
		renderer->pushTransform(m_Transform.getMatrix());

		for (const Renderable2D* renderable : m_Renderables)
			renderable->onSubmit(renderer);

		renderer->popTransform();
	}

} }