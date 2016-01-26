#pragma once

#include <nw/Types.h>
#include <nw/gfx/IndexBuffer.h>

namespace nw { namespace gfx { 

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_COLOR_INDEX 2

#define RENDERER_MAX_SPRITES	50000	// per Draw Call
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

class NW_API SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Bind();
	void Submit(const Renderable2D* renderable);
	void Unbind();
	void Display();

private:
	uint m_VAO;
	uint m_VBO;
	IndexBuffer* m_IBO;
	uint m_IndexCount;
	VertexData* m_Buffer;
};

} }