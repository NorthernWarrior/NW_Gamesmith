#include "src/input/Input.h"
#include "src/maths/Maths.h"
#include "src/utils/File.h"
#include "src/graphics/Shader.h"
#include "src/graphics/Rendering2D/BatchRenderer2D.h"
#include "src/graphics/Rendering2D/Sprite.h"
#include "src/graphics/Buffer/IndexBuffer.h"
#include "src/graphics/Color.h"

using namespace gamesmith;
using namespace graphics;
using namespace maths;
using namespace input;

#include <vector>

int main()
{
	Window window;
	window.create("Gamesmith", 800, 400);

	Shader* diffuse = Shader::create("data/shader/diffuse.vert", "data/shader/diffuse.frag");
	mat4 pr_matrix = mat4::orthographic(-2, 2, -1, 1, -1, 1);

	Renderer2D* renderer = new BatchRenderer2D;

	std::vector<Renderable2D> sprites;
	float hor = 20, vert = 10;
	float w = 4 / hor, h = 2 / vert;
	for (int y = 0; y < vert; ++y)
	{
		for (int x = 0; x < hor; ++x)
			sprites.push_back(Sprite(vec2f(-2 + (x*w), -1 + (y*h)), vec2f(w-(w*0.1), h-(h*0.1)), Color::fromRGBA(vec4f((rand() % 256) / 255.f, 0, 0.5, 1.f))));
	}
	std::cout << sprites.size() << " Sprites" << std::endl;
	Sprite back(vec2f(-2, -1), vec2f(4, 2), 0);

	double lastTime = glfwGetTime();
	double currentTime = 0;
	int frameCnt = 0;
	while (window.run())
	{
		diffuse->bind();
		diffuse->SetUniformMat4("pr_matrix", pr_matrix);
		diffuse->SetUniformVec2("light_pos", vec2f((Mouse::GetPosition().x - window.getWidth() / 2) / (window.getWidth() / 2), -(Mouse::GetPosition().y - window.getHeight() / 2) / (window.getHeight() / 2)));

		renderer->bind();
		renderer->submit(back);
		for (Renderable2D r : sprites)
			renderer->submit(r);
		renderer->unbind();

		renderer->display();

		++frameCnt;
		currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0)
		{
			std::cout << 1000.0 / frameCnt << " - " << frameCnt << std::endl;
			frameCnt = 0;
			lastTime += 1.0;
		}

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