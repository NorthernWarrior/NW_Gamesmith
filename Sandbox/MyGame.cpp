#include <Gamesmith.h>

#include <iostream>
#include <vector>
#include <time.h>

using namespace nw;
using namespace gfx;
using namespace input;
using namespace math;

class MyGame : public Gamesmith
{
public:
	MyGame()
	{
#ifdef _DEBUG
		m_WindowOptions.Vsync = false;
		m_WindowOptions.Samples = 4;
#else
		m_WindowOptions.Samples = 8;
#endif
		m_WindowOptions.CanResize = true;
	}

	~MyGame()
	{
		delete m_Renderer;
		for (auto sprite : m_Sprites)
			delete sprite;
		delete m_Shader;
	}

private:
	void OnInitialise() override
	{
		srand(time(nullptr));

		m_Shader = Shader::Create(Shader::Texture);

		m_Renderer = new SpriteRenderer();

		byte pixels[] = {
			255, 0, 0,
			0, 255, 0,

			0, 0, 255,
			255, 255, 0,

			255, 0, 0,
			0, 255, 0,

			255, 0, 0,
			0, 255, 0,

			0, 0, 255,
			255, 255, 0,

			0, 0, 255,
			255, 255, 0,

			0, 0, 255,
			255, 255, 0,

			255, 0, 0,
			0, 255, 0,
		};

		m_Texture.Create(4, 4, pixels, 24);

		int X = 10, Y = 10;
		float dimension = 32;
		pr_matrix = Matrix4::Orthographic(0, 900, 450, 0, -1, 1);

		for (int x = 0; x < X; ++x)
		{
			for (int y = 0; y < Y; ++y)
			{
				m_Sprites.push_back(new Sprite(Vector2(40 + x*dimension + dimension, 25 + y*dimension + dimension), 0xFFFFFFFF, Vector2(dimension, dimension)));
			}
		}
		std::cout << "Created: " << m_Sprites.size() << std::endl;
	}

	void OnUpdate() override
	{
		if (Keyboard::GetKeyUp(Keyboard::Escape))
			Quit();
	}

	void OnRender() override
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("pr_matrix", pr_matrix);

		m_Texture.Bind();
		m_Renderer->Bind();
		for (auto sprite : m_Sprites)
		{
			m_Renderer->Submit(sprite);
		}
		m_Renderer->Unbind();
		m_Renderer->Display();
		m_Texture.Unbind();
	}

private:
	SpriteRenderer* m_Renderer;
	Shader* m_Shader;
	std::vector<Sprite*> m_Sprites;
	Matrix4 pr_matrix;
	Texture2D m_Texture;
};


// The Main Function
int main()
{
	return MyGame().Start();
}