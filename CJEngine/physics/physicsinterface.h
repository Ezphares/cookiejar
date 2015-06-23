#pragma once

#include <foundation/vector.h>

#include <componentmodel/entity.h>

#include <cstdint>

namespace cookiejar
{
	typedef std::uint32_t CollisionEvent;
	const CollisionEvent PUSH_LEFT = 1;
	const CollisionEvent PUSH_RIGHT = 2;
	const CollisionEvent PUSH_UP = 4;
	const CollisionEvent PUSH_DOWN = 8;
	const CollisionEvent CRUSH_H = PUSH_LEFT | PUSH_RIGHT;
	const CollisionEvent CRUSH_V = PUSH_UP | PUSH_DOWN;

	typedef std::uint32_t TriggerType;
	const static TriggerType NOT_TRIGGER = 0;
	struct TriggerEvent
	{
		TriggerType type;
		Entity entity;
	};

	bool place_free(const Entity &entity, Vector2 position);
}
