#pragma once

#include <foundation/activatable.h>

#include <window/graphics/glgraphicscontroller.h>
#include <window/graphics/sprite.h>

namespace cookiejar
{
	class DrawManager : public Activatable<DrawManager>
	{
	public:
		DrawManager();
		~DrawManager();

	public:
		void draw_sprite(Sprite *sprite, const int &frame, const Vector2 &position);

	private:
		GraphicsController *_controller;
	};
}
