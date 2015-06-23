#include <iostream>

#include "foundation/quadtree.h"
#include "world\game.h"
#include "window\graphics\sprite.h"
#include "drawing\spritedrawcomponent.h"
#include "physics\collidercomponent.h"
#include "behaviour/behaviourcomponent.h"

#include "interfaces.h"

#include <Windows.h>

using namespace cookiejar;

Texture *tex_block = NULL;
Sprite *spr_block = NULL;

void block(BasePrecision x, BasePrecision y)
{
	Entity n = entity_create(Vector2{ x, y });

	std::shared_ptr<SpriteDraw> spr(new SpriteDraw(spr_block));
	component_attach<Draw>(n, spr);

	std::shared_ptr<Collider> col(new Collider(Rect<BasePrecision>({ 0, 0 }, { 32, 32 })));
	col->solid = true;
	col->layers = 1;
	component_attach<Collider>(n, col);
}


CJ_BEHAVIOUR_SCRIPT(gravity)
{
	auto trans = component_get<Translation>(self);
	if (place_free(self, trans->position + Vector2{0, 1}) || trans->velocity.y < 0)
	{
		trans->velocity.y = std::min(trans->velocity.y + 1.0, 190.0);
	}
	else
	{
		trans->velocity.y = 0;
	}
}

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

	BoundingBox o = Rect<BasePrecision>({ 0, 0 }, { 32, 32 }),
		p = Rect<BasePrecision>({ 0, 32 }, { 32, 32 });

	std::cout << o.intersects(p);
	
	Texture tx("spr.png");
	Sprite spr(&tx, 1, 1, Point < int32_t > {32, 32}, Point < int32_t > {0, 0}, Point < int32_t > {0, 0});

	// MOVER
	Entity e1 = entity_create(Vector2{0, 300});
	component_get<Translation>(e1)->velocity = { 100, 0};

	std::shared_ptr<SpriteDraw> sd1(new SpriteDraw(&spr));
	component_attach<Draw>(e1, sd1);

	std::shared_ptr<Collider> c1(new Collider(Rect<BasePrecision>({ 0, 0 }, { 32, 32 })));
	c1->blocked = true;
	c1->layers = 1;
	component_attach<Collider>(e1, c1);

	std::shared_ptr<Behaviour> b1(new Behaviour());
	b1->update = gravity;
	component_attach<Behaviour>(e1, b1);
	
	// INPUT
	tex_block = new Texture("brickbase.png");
	spr_block = new Sprite(tex_block, 1, 1, Point < int32_t > {32, 32}, Point < int32_t > {0, 0}, Point < int32_t > {0, 0});

	for (int i = 0; i < 800; i += 32)
	{
		block((float)i, (float)(600 - 32));
	}

	game.run();
	
	return 0;
}
