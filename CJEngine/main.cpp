#include <iostream>

#include "foundation/quadtree.h"
#include "world\game.h"
#include "window\graphics\sprite.h"
#include "drawing\spritedrawcomponent.h"
#include "physics\collidercomponent.h"

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

	// MOVER
	Entity e = entity_create(Vector2{0, 0});
	component_get<Translation>(e)->velocity = { 100, 0};

	SpriteDraw sd(&spr);
	component_attach<Draw>(e, &sd);

	Collider c(Rect<float>({ 0, 0 }, { 32, 32 }));

	c.blocked = true;
	c.layers = 1;
	component_attach<Collider>(e, &c);

	// BLOCK
	Entity e2 = entity_create(Vector2{ 100, 0 });

	SpriteDraw sd2(&spr);
	component_attach<Draw>(e2, &sd2);

	Collider c2(Rect<float>({ 0, 0 }, { 32, 32 }));
	c2.solid = true;
	c2.layers = 1;
	component_attach<Collider>(e2, &c2);


	game.run();
	
	return 0;
}
