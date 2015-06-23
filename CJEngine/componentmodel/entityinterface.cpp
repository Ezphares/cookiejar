#include "entityinterface.h"
#include "entitymanager.h"
#include <physics/translationcomponent.h>

namespace cookiejar
{
	bool entity_is_alive(const Entity &entity)
	{
		return EntityManager::active()->is_alive(entity);
	}

	Entity entity_create(const Vector2 &translation)
	{
		auto trans = std::shared_ptr<Translation>(new Translation(translation));
		
		Entity e = EntityManager::active()->create_entity();
		component_attach<Translation>(e, trans);
		return e;
	}


	Vector2 *entity_position(const Entity &entity)
	{
		return &component_get<Translation>(entity)->position;
	}
}
