#pragma once

#include <foundation/vector.h>

namespace cookiejar
{
	struct Entity;


	Entity entity_create(const Vector2 &translation);
	bool entity_is_alive(const Entity &entity);
}
