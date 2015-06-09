#include <iostream>

#include "foundation/quadtree.h"
#include "componentmodel\translationcomponent.h"
#include "world\game.h"
#include "window\graphics\sprite.h"

#include <Windows.h>

using namespace cookiejar;

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	Game game{};
	game.window_settings.size = { 800, 600 };
	game.window_settings.caption = "Test";
	game.window_settings.fullscreen = false;

	game.run();

	//Vector2 a{ 1, 2 };
	//a += Vector2{ 1, 2 };

	//BoundingBox bb{ Vector2{ 0, 0 }, 100.0, 100.0 };

	//QuadTree q{ bb };
	//std::cout << q.insert(a) << std::endl;
	return 0;
}
