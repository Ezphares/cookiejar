#include "physicsmanager.h"

#include "collidercomponent.h"
#include "translationcomponent.h"

namespace cookiejar
{
	PhysicsManager::PhysicsManager(const BoundingBox &area) :
		_collider_tree(area),
		_translations()
	{
	}

	PhysicsManager::~PhysicsManager()
	{
		for (Translation *t : _translations)
		{
			delete t;
		}
	}

	Translation *PhysicsManager::get_translation(const Entity &entity)
	{
		return _translations[entity.index()];
	}

	void PhysicsManager::attach_translation(const Entity &entity, Translation *translation)
	{
		auto index = entity.index();
		while (_translations.size() <= index)
		{
			_translations.push_back(NULL);
		}

		delete _translations[index];
		_translations[index] = translation;
	}

	void PhysicsManager::update(float delta)
	{
		for (Translation *t : _translations)
		{
			t->position += (t->velocity * delta);
		}
	}
}
