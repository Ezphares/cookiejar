#include "entityinterface.h"
#include "entitymanager.h"
#include "translationcomponent.h"

namespace cookiejar
{
	static EntityManager *ACTIVE = NULL;

	bool entity_is_alive(const Entity &entity)
	{
		return ACTIVE->is_alive(entity);
	}

	Entity entity_create(const Vector2 &translation)
	{
		Entity e = ACTIVE->create_entity();
		component_attach(e, Translation(translation));
		return e;
	}
}
