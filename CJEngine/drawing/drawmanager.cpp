#include "drawmanager.h"

namespace cookiejar
{
	DrawManager::DrawManager()
	{
	}


	DrawManager::~DrawManager()
	{
	}

	void DrawManager::draw_sprite(Sprite *sprite, const int &frame, const Vector2 &position)
	{
		sprite->get_texture()->bind();
		_controller->draw_textured_rectangle(
			position,
			sprite->get_size(),
			sprite->get_offset(frame),
			sprite->get_framesize());
	}
}
