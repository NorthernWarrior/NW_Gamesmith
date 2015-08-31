#pragma once

#include "Renderer2D.h"

#include "../Buffer/IndexBuffer.h"

namespace gamesmith { namespace graphics {

#define RENDERER_MAX_SPRITES	50000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32 - 1

	class BatchRenderer2D : public Renderer2D
	{
	private:
		uint m_VAO;
		uint m_VBO;
		IndexBuffer* m_IBO;
		uint m_IndexCount;
		VertexData* m_Buffer;

	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void bind() override;
		void submit(const Renderable2D& renderable) override;
		void unbind();
		void display() override;

	};

} }