#pragma once

#include <nw/Types.h>
#include <nw/gfx/IndexBuffer.h>

#include <climits>
#include <vector>

namespace nw { namespace gfx { 

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_COLOR_INDEX 2
#define SHADER_TEXID_INDEX 3

#define RENDERER_INDICES_SIZE	USHRT_MAX
#define RENDERER_MAX_SPRITES	RENDERER_INDICES_SIZE / 6	// per Draw Call
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_MAX_TEXTURES	32 - 1

class NW_API SpriteRenderer
{
public:
	SpriteRenderer(Shader* shader);
	~SpriteRenderer();

	void Bind();
	void Submit(const Sprite* renderable);
	void Unbind();
	void Display(bool keepData = false);

private:
	float RegisterTexture(uint textureID);
	float RegisterTexture(const Texture2D& texture);

private:
	uint m_VAO;
	uint m_VBO;
	IndexBuffer* m_IBO;
	uint m_IndexCount;
	uint m_SpriteCount;
	VertexData* m_Buffer;
	std::vector<uint> m_TextureIDs;
	Shader* m_Shader;
};

} }