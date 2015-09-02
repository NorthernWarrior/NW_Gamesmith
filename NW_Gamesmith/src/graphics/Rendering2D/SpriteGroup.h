#pragma once

#include <vector>

#include "Renderable2D.h"

namespace gamesmith { namespace graphics {

	class SpriteGroup : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;

	public:
		SpriteGroup(maths::vec2f position);
		~SpriteGroup();

		Renderable2D* add(Renderable2D* renderable);
		void onSubmit(Renderer2D* renderer) const override;
	};

} }