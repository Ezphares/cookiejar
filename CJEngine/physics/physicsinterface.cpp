#include "physicsinterface.h"

#include "physicsmanager.h"

namespace cookiejar
{
	bool place_free(const Entity &entity, Vector2 target)
	{
		return PhysicsManager::active()->is_free(entity, target, true);
	}
}
