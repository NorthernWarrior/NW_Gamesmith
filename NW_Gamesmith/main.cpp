#include <vector>
#include <time.h>

#include "src/input/Input.h"
#include "src/maths/Maths.h"
#include "src/utils/File.h"
#include "src/utils/Message.h"
#include "src/graphics/Shader/ShaderManager.h"
#include "src/graphics/RenderLayer/TileLayer.h"
#include "src/graphics/Rendering2D/BatchRenderer2D.h"
#include "src/graphics/Rendering2D/Sprite.h"
#include "src/graphics/Buffer/IndexBuffer.h"
#include "src/graphics/Color.h"
#include "src/graphics/TextureManager2D.h"
#include <FreeImage/FreeImage.h>

using namespace gamesmith;
using namespace graphics;
using namespace maths;
using namespace input;

int main()
{
	srand(time(nullptr));

	Window window;
	window.setBackground(vec3f(0, 0, 0));
	window.create("Gamesmith", 800, 400);

	Shader* diffuse = ShaderManager::addFromFile("diffuse", "data/shader/diffuse.vert", "data/shader/diffuse.frag");
	mat4 pr_matrix = mat4::orthographic(-(window.getWidth() / 2.f), (window.getWidth() / 2), (window.getHeight() / 2.f), 0.0f-(window.getHeight() / 2), -1, 1);

	TileLayer backLayer(new BatchRenderer2D, diffuse);
	TileLayer layer(new BatchRenderer2D, diffuse);

	Texture2D* backTex = TextureManager2D::addFromFile("back", "data/gfx/back.png");
	Sprite* back = new Sprite();
	backLayer.add(back);

	int spriteCnt = 0;
	std::vector<vec2f>targets;
	std::vector<vec2f>velocities;
#if _DEBUG
	float hor = 10, vert = 2;
	float w = 16, h = 16;
#else
	float hor = 100, vert = 20;
	float w = 16, h = 16;
#endif
	for (int y = 0; y < vert; ++y)
	{
		for (int x = 0; x < hor; ++x)
		{
			vec2f pos(-(window.getWidth() / 2.f) + w / 2 + (x*w) + ((w / 2)*0.025), -(window.getHeight() / 2.f) + h / 2 + (y*h) + ((h / 2)*0.025));
			layer.add(new Sprite(pos, vec2f(w - (w*0.05), h - (h*0.05)), Color::fromRGBA(255, (rand() % 256), 0, 255)));
			targets.push_back(vec2f(rand() % 1000 - 500, rand() % 1000 - 500));
			velocities.push_back(vec2f());
			++spriteCnt;
		}
	}

	Texture2D* myTex = TextureManager2D::addFromFile("player", "data/gfx/player.png");
	Sprite* player = new Sprite();
	player->setSize(vec2f(64, 64));
	layer.add(player);

	double lastTime = glfwGetTime();
	double currentTime = 0;
	double begin = 0;
	double dt = 0;
	int frameCnt = 0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double speed = 0;
	while (window.run())
	{
		speed = 2000 * dt;
		begin = glfwGetTime();

		diffuse->bind();
		pr_matrix = mat4::orthographic(-(window.getWidth() / 2.f), (window.getWidth() / 2), (window.getHeight() / 2.f), 0.0f-(window.getHeight() / 2), -1, 1);
		back->setSize(vec2f(window.getWidth(), window.getHeight()));
		diffuse->SetUniformMat4("pr_matrix", pr_matrix);

		vec2f target = player->getTransform()->getPosition();//Mouse::getPosition() - (vec2f(window.getWidth(), window.getHeight()) / 2.0f);
		diffuse->SetUniformVec2("light_pos", target);
		for (int i = 0; i < spriteCnt; ++i)
		{
			Renderable2D* curr = layer.getRenderable(i);
			auto pos = curr->getTransform()->getPosition();
			float dist = pos.distance(targets[i]);
			if (dist <= 500.0f)
				targets[i] = vec2f(target.x + rand()%2 - 1, target.y + rand() % 2 - 1);
			velocities[i] += (targets[i] - pos).normalise() * speed;
			velocities[i].x = clamp(velocities[i].x, -1000.f, 1000.f);
			velocities[i].y = clamp(velocities[i].y, -1000.f, 1000.f);
			curr->setColor(Color::fromRGBA(255, clamp<float>(abs(pos.distance(target) / 5.f), 0, 150), 0, 255));
			curr->setPosition(pos + (velocities[i] * dt));
		}

		backTex->bind();
		backLayer.render();

		myTex->bind();
		layer.render();


		dt = glfwGetTime() - begin;

		++frameCnt;
		currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0)
		{
			std::cout << 1000.0 / frameCnt << " - " << frameCnt << std::endl;
			frameCnt = 0;
			lastTime += 1.0;
		}

		if (Keyboard::getKey(Keyboard::Key::W))
			player->setPosition(player->getTransform()->getPosition() + vec2f(0, -speed));
		else if (Keyboard::getKey(Keyboard::Key::S))
			player->setPosition(player->getTransform()->getPosition() + vec2f(0, speed));

		if (Keyboard::getKey(Keyboard::Key::A))
			player->setPosition(player->getTransform()->getPosition() + vec2f(-speed, 0));
		else if (Keyboard::getKey(Keyboard::Key::D))
			player->setPosition(player->getTransform()->getPosition() + vec2f(speed, 0));

		if (Keyboard::getKey(Keyboard::Key::Q))
			player->getTransform()->setRotation(player->getTransform()->getRotation() - (speed/2));
		else if (Keyboard::getKey(Keyboard::Key::E))
			player->getTransform()->setRotation(player->getTransform()->getRotation() + (speed/2));


	}

	return EXIT_SUCCESS;
}





#if 0 // Empty namespace for copying - just because im lazy

namespace gamesmith { namespace graphics {



} }

#endif