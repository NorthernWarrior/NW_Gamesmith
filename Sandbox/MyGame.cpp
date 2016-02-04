#include <Gamesmith.h>

#include <iostream>
#include <vector>
#include <time.h>

using namespace nw;
using namespace gfx;
using namespace input;
using namespace math;
using namespace rm;

class MyGame : public Gamesmith
{
public:
	MyGame()
	{
#ifdef _DEBUG
		m_WindowOptions.VSync = false;
		m_WindowOptions.Samples = 4;
#else
		m_WindowOptions.Samples = 8;
#endif
		m_WindowOptions.CanResize = true;
		m_WindowOptions.SetSize(Vector2(1422, 800));
	}

private:
	Vector2 center;

	void OnInitialise() override
	{
		srand(static_cast<int>(time(nullptr)));

		m_Renderer = new SpriteRenderer(Shader::Create(Shader::Texture));

		ResourceManager::LoadFromFile<Texture2D>("C:/Users/Tobias/Documents/Visual Studio 2015/Projects/C++/NW_Gamesmith/Resources/pig.png", "pig");
		ResourceManager::LoadFromFile<Texture2D>("C:/Users/Tobias/Documents/Visual Studio 2015/Projects/C++/NW_Gamesmith/Resources/logo.png", "logo");
		ResourceManager::LoadFromFile<Texture2D>("C:/Users/Tobias/Documents/Visual Studio 2015/Projects/C++/NW_Gamesmith/Resources/tile.png", "tile");

		m_Back = new Sprite(Vector2(static_cast<float>(m_WindowOptions.Width) / 2, static_cast<float>(m_WindowOptions.Height) / 2), 0xFF111111, Vector2(static_cast<float>(m_WindowOptions.Width * 2), static_cast<float>(m_WindowOptions.Height * 2)));

		center = Vector2(static_cast<float>(m_WindowOptions.Width / 6), static_cast<float>(m_WindowOptions.Height / 2));
		m_Pig = new Sprite(center, ResourceManager::Get<Texture2D>("pig"));
		m_Pig->SetSize(Vector2(256, 256));

		m_Logo = new Sprite(Vector2(64, 64), ResourceManager::Get<Texture2D>("logo"));
		m_Logo->SetSize(Vector2(128, 128));

		NW_FOR_2D(45, 25)
			m_Tilemap.push_back(new Sprite(Vector2(static_cast<float>(x * 32 + 16), static_cast<float>(y * 32 + 16)), ResourceManager::Get<Texture2D>("tile")));

		//m_Cam = new Camera(0, static_cast<float>(m_WindowOptions.Width), 0, static_cast<float>(m_WindowOptions.Height));
		float width = static_cast<float>(m_WindowOptions.Width / 3);
		m_Cam = new Camera(0, width-2, 0, static_cast<float>(m_WindowOptions.Height));
		m_Cam2 = new Camera(width + 2, width - 2, 0, static_cast<float>(m_WindowOptions.Height));
		m_Cam3 = new Camera(width + 2 + width + 2, width - 2, 0, static_cast<float>(m_WindowOptions.Height));
	}

	void OnUpdate() override
	{
		if (Keyboard::GetKeyUp(Keyboard::Escape))
			Quit();

		float speed = 400;
		if (Keyboard::GetKey(Keyboard::W))
			m_Pig->SetPosition(m_Pig->GetPosition() + (Vector2::Down() * speed * Time::GetDeltaTime()));
		else if (Keyboard::GetKey(Keyboard::S))
			m_Pig->SetPosition(m_Pig->GetPosition() + (Vector2::Up() * speed * Time::GetDeltaTime()));
		if (Keyboard::GetKey(Keyboard::A))
			m_Pig->SetPosition(m_Pig->GetPosition() + (Vector2::Left() * speed * Time::GetDeltaTime()));
		else if (Keyboard::GetKey(Keyboard::D))
			m_Pig->SetPosition(m_Pig->GetPosition() + (Vector2::Right() * speed * Time::GetDeltaTime()));

		if (Keyboard::GetKey(Keyboard::Up))
			m_Cam2->GetTransform()->Translate((Vector2::Down() * speed * Time::GetDeltaTime()));
		else if (Keyboard::GetKey(Keyboard::Down))
			m_Cam2->GetTransform()->Translate((Vector2::Up() * speed * Time::GetDeltaTime()));
		if (Keyboard::GetKey(Keyboard::Left))
			m_Cam2->GetTransform()->Translate((Vector2::Left() * speed * Time::GetDeltaTime()));
		else if (Keyboard::GetKey(Keyboard::Right))
			m_Cam2->GetTransform()->Translate((Vector2::Right() * speed * Time::GetDeltaTime()));

		m_Cam->GetTransform()->SetPosition(m_Pig->GetPosition() - center);
	}

	void OnRender() override
	{
		m_Renderer->Bind();
		m_Renderer->Submit(m_Back);
		for (auto sprite : m_Tilemap)
			m_Renderer->Submit(sprite);
		m_Renderer->Submit(m_Pig);
		m_Renderer->Submit(m_Logo);
		m_Renderer->Unbind();

		m_Cam->SetActive();
		m_Renderer->Display(true);

		m_Cam2->SetActive();
		m_Renderer->Display(true);

		m_Cam3->SetActive();
		m_Renderer->Display();
	}

private:
	SpriteRenderer* m_Renderer;
	Sprite* m_Back;
	Sprite* m_Pig;
	std::vector<Sprite*> m_Tilemap;
	Sprite* m_Logo;
	Camera* m_Cam;
	Camera* m_Cam2;
	Camera* m_Cam3;
};


// The Main Function
int main()
{
	return MyGame().Start();
}