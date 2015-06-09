#pragma once

#include "drawcomponent.h"

#include <componentmodel\translationcomponent.h>
#include <window\graphics\sprite.h>

namespace cookiejar
{
	CJ_BEHAVIOUR_SCRIPT(sprite_draw_behaviour);

	class SpriteDraw : public Draw
	{
	public:
		inline SpriteDraw(Sprite *sprite, const Vector2 &offset = { 0, 0 }, const int &depth = 0, const float &fps = 30) : Draw(sprite_draw_behaviour, depth),
			sprite(sprite),
			offset(offset),
			fps(fps),
			accumulator(0.0),
			frame(0)
		{}

		Sprite *sprite;
		Vector2 offset;
		float fps, accumulator;
		int frame;
	};

	CJ_BEHAVIOUR_SCRIPT(sprite_draw_behaviour)
	{
		SpriteDraw &cmp = *dynamic_cast<SpriteDraw *>(component);
		float delta = *(float *)(arg);

		cmp.accumulator += delta;
		float spf = 1 / cmp.fps;
		while (cmp.accumulator > spf)
		{
			cmp.accumulator -= spf;
			cmp.frame = (cmp.frame + 1) % cmp.sprite->get_frames();
		}

		Vector2 pos = component_get<Translation>(self)->pos + cmp.offset;
		draw_sprite(cmp.sprite, cmp.frame, pos);
	}
}
