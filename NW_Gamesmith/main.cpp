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

using namespace gamesmith;
using namespace graphics;
using namespace maths;
using namespace input;

int main()
{
	srand(time(nullptr));

	Window window;
	window.create("Gamesmith", 800, 400);

	Shader* diffuse = ShaderManager::addFromFile("diffuse", "data/shader/diffuse.vert", "data/shader/diffuse.frag");
	mat4 pr_matrix = mat4::orthographic(-(window.getWidth() / 2.f), (window.getWidth() / 2), - (window.getHeight() / 2.f), (window.getHeight() / 2), -1, 1);

	TileLayer layer(new BatchRenderer2D, diffuse);

	layer.add(new Sprite(vec2f(-(window.getWidth() / 2.f), -(window.getHeight() / 2.f)), vec2f(window.getWidth(), window.getHeight()), 0));
	float hor = 10, vert = 5;
	float w = window.getWidth() / hor, h = window.getHeight() / vert;
	for (int y = 0; y < vert; ++y)
	{
		for (int x = 0; x < hor; ++x)
			layer.add(new Sprite(vec2f(-(window.getWidth() / 2.f) + (x*w) + (w*0.025), -(window.getHeight() / 2.f) + (y*h) + (h*0.025)), vec2f(w-(w*0.05), h-(h*0.05)), Color::fromRGBA(vec4f((rand() % 256) / 255.f, 0, 0.5, 1.f))));
	}
	auto player = layer.add(new Sprite(vec2f(-50, -50), vec2f(100, 100), 0xff333333));

	double lastTime = glfwGetTime();
	double currentTime = 0;
	int frameCnt = 0;
	while (window.run())
	{
		diffuse->bind();
		pr_matrix = mat4::orthographic(-(window.getWidth() / 2.f), (window.getWidth() / 2), -(window.getHeight() / 2.f), (window.getHeight() / 2), -1, 1);
		diffuse->SetUniformMat4("pr_matrix", pr_matrix);
		diffuse->SetUniformVec2("light_pos", vec2f((Mouse::GetPosition().x - window.getWidth() / 2), -(Mouse::GetPosition().y - window.getHeight() / 2)));

		layer.render();

		++frameCnt;
		currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0)
		{
			std::cout << 1000.0 / frameCnt << " - " << frameCnt << std::endl;
			frameCnt = 0;
			lastTime += 1.0;
		}



		if (Keyboard::GetKey(Keyboard::Key::W))
			player->setPosition(player->getTransform().getPosition() + vec2f(0, 0.25));
		else if (Keyboard::GetKey(Keyboard::Key::S))
			player->setPosition(player->getTransform().getPosition() + vec2f(0, -0.25));

		if (Keyboard::GetKey(Keyboard::Key::A))
			player->setPosition(player->getTransform().getPosition() + vec2f(-0.25, 0));
		else if (Keyboard::GetKey(Keyboard::Key::D))
			player->setPosition(player->getTransform().getPosition() + vec2f(0.25, 0));

		if (Keyboard::GetKeyUp(Keyboard::F5))
		{
			diffuse->reload();
			diffuse->bind();
		}
	}

	return EXIT_SUCCESS;
}





#if 0 // Empty namespace

namespace gamesmith { namespace graphics {



} }

#endif