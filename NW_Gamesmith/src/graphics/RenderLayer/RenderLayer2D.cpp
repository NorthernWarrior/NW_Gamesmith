#include "RenderLayer2D.h"

namespace gamesmith { namespace graphics {

	RenderLayer2D::~RenderLayer2D()
	{
		if (m_Renderer != nullptr)
			delete m_Renderer;
	}

} }