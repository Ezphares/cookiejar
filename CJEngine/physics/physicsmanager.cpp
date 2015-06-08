#include "physicsmanager.h"

#include "collidercomponent.h"

namespace cookiejar
{
	PhysicsManager::PhysicsManager(const BoundingBox &area) :
		_collider_tree(area)
	{
	}

	PhysicsManager::~PhysicsManager()
	{
	}
}
