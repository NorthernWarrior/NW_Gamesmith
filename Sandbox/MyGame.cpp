#include <Gamesmith.h>

#include <iostream>
#include <vector>

using namespace nw;
using namespace gfx;
using namespace input;
using namespace math;

unsigned int colors[] = {
	0xFF000000,
	0xFFFFFFFF,
	0xFFFFFF00,
	0xFF00FF00,
	0xFFFF0000,
	0xFF0000FF,

	0xFF999999,
	0xFF999900,
	0xFF990099,
	0xFF000099,
};

class MyGame : public Gamesmith
{
public:
	~MyGame()
	{
		delete m_Renderer;
		//delete m_Sprite;
		delete m_Shader;
	}

private:
	void OnInitialise() override
	{
		m_Shader = Shader::Create(Shader::Diffuse);

		m_Renderer = new SpriteRenderer();
		//m_Sprite = new Sprite(Vector2(450, 300), 0xffffff23, Vector2(200, 200));



		int X = 200, Y = 100;
		float dimension = 4;
		pr_matrix = Matrix4::Orthographic(0, 900, 450, 0, -1, 1);

		for (int x = 0; x < X; ++x)
		{
			for (int y = 0; y < Y; ++y)
			{
				int i = (rand() % (sizeof(colors) / (sizeof(unsigned int))));
				if (y == Y - 1 || x == X - 1)
					i = 0;
				m_Sprites.push_back(new Sprite(Vector2(40 + x*dimension + dimension, 25 + y*dimension + dimension), colors[i], Vector2(dimension, dimension)));
			}
		}
		std::cout << "Created: " << m_Sprites.size() << std::endl;
	}

	void OnUpdate() override
	{
		if (Keyboard::GetKeyUp(Keyboard::Escape))
			Quit();
	}

	bool randomColors = false;
	void OnRender() override
	{
		if (Keyboard::GetKeyUp(Keyboard::F1))
			randomColors = !randomColors;

		m_Shader->Bind();
		m_Shader->SetUniformMat4("pr_matrix", pr_matrix);

		m_Renderer->Bind();
		for (auto sprite : m_Sprites)
		{
			if (randomColors)
			{
				int i = (rand() % (sizeof(colors) / (sizeof(unsigned int))));
				sprite->SetColor(colors[i]);
			}
			m_Renderer->Submit(sprite);
		}
		m_Renderer->Unbind();
		m_Renderer->Display();
	}

private:
	SpriteRenderer* m_Renderer;
	Shader* m_Shader;
	std::vector<Sprite*> m_Sprites;
	Matrix4 pr_matrix;
};


// The Main Function
int main()
{
	return MyGame().Start();
}