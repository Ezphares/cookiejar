#include <iostream>

#include "foundation/quadtree.h"
#include "componentmodel\translationcomponent.h"
#include "world\game.h"
#include "window\graphics\sprite.h"
#include "drawing\spritedrawcomponent.h"

#include "interfaces.h"

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

	game.initialize();
	game.create_room(true);

	
	Texture tx("spr.png");
	Sprite spr(&tx, 1, 1, Point < int32_t > {32, 32}, Point < int32_t > {0, 0}, Point < int32_t > {0, 0});

	Entity e = entity_create(Vector2{0, 0});
	std::cout << entity_is_alive(e) << std::endl;

	SpriteDraw sd(&spr);

	component_attach<Draw>(e, &sd);

	game.run();
	
	//Vector2 a{ 1, 2 };
	//a += Vector2{ 1, 2 };

	//BoundingBox bb{ Vector2{ 0, 0 }, 100.0, 100.0 };

	//QuadTree q{ bb };
	//std::cout << q.insert(a) << std::endl;
	return 0;
}
