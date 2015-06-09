#include "drawinterface.h"

#include "drawmanager.h"

namespace cookiejar
{
	void draw_sprite(Sprite *sprite, int frame, Vector2 position)
	{
		DrawManager::active()->draw_sprite(sprite, frame, position);
	}
}
