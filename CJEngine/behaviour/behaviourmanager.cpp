#include "behaviourmanager.h"

#include "behaviourcomponent.h"

#include <componentmodel/entitymanager.h>

namespace cookiejar
{
	BehaviourManager::BehaviourManager() :
		_to_init(),
		_created(),
		_destroyed(),
		_behaviours()
	{
	}


	BehaviourManager::~BehaviourManager()
	{
	}

	void BehaviourManager::attach_behaviour(const Entity &entity, std::shared_ptr<Behaviour> behaviour)
	{
		_to_init.push_back(behaviour);
		_behaviours[entity].push_back(behaviour);
	}

	void BehaviourManager::update(float delta)
	{
		// INIT
		for (auto b : _to_init)
		{
			Entity e = b->get_entity();
			if (entity_is_alive(e))
			{
				b->init(e, b.get(), NULL);
			}
		}
		_to_init.clear();

		// CREATE
		for (auto e : _created)
		{
			if (entity_is_alive(e))
			{
				for (auto b : _behaviours[e])
				{
					b->create(e, b.get(), NULL);
				}
			}
		}
		_created.clear();

		// UPDATE
		for (auto it = _behaviours.begin(); it != _behaviours.end();)
		{
			Entity e = it->first;
			if (!entity_is_alive(e))
			{
				_behaviours.erase(it++);
			}
			else
			{
				for (auto b : it->second)
				{
					b->update(e, b.get(), NULL);
				}
				++it;
			}
		}
	}

	void BehaviourManager::post_update(float delta)
	{
		// UPDATE
		for (auto it = _behaviours.begin(); it != _behaviours.end();)
		{
			Entity e = it->first;
			if (!entity_is_alive(e))
			{
				_behaviours.erase(it++);
			}
			else
			{
				for (auto b : it->second)
				{
					b->post_update(e, b.get(), NULL);
				}
				++it;
			}
		}

		// DESTROY
		for (auto e : _destroyed)
		{
			if (entity_is_alive(e))
			{
				for (auto b : _behaviours[e])
				{
					b->destroy(e, b.get(), NULL);
				}
			}
			EntityManager::active()->destroy_entity(e);
		}
		_destroyed.clear();

	}
}
