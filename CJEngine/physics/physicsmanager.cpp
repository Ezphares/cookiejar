#include "physicsmanager.h"

#include "collidercomponent.h"
#include "translationcomponent.h"

#include <foundation/algorithm.h>

#include <cmath>

namespace cookiejar
{
	PhysicsManager::PhysicsManager(const BoundingBox &area) :
		_collider_all(),
		_collider_tree(area),
		_collider_oob(),
		_translations(),
		_range(0.0)
	{
	}

	PhysicsManager::~PhysicsManager()
	{
		for (Translation *t : _translations)
		{
			delete t;
		}

		for (Collider *c : _collider_all)
		{
			delete c;
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

	void PhysicsManager::attach_collider(const Entity &entity, Collider *collider)
	{
		_collider_all.push_back(collider);

		float new_range = std::max(collider->boundary.halfheight, collider->boundary.halfwidth) * 2;
		_range = std::max(_range, new_range);
		if (!_collider_tree.insert(collider))
		{
			_collider_oob.push_back(collider);
		}

		std::cout << "COLLIDE ALL" << std::endl;

	}

	void PhysicsManager::update(float delta)
	{
		// Update positions
		for (Translation *t : _translations)
		{
			t->position_previous = t->position;
			t->position += (t->velocity * delta);
		}

		// Make sure tree contains correct elements
		std::vector<Collider *> out = _collider_tree.update();

		auto in = _collider_oob.begin();
		while (in != _collider_oob.end())
		{
			Collider *c = (*in);
			if (_collider_tree.insert(c))
			{
				in = _collider_oob.erase(in);
			}
			else
			{
				in++;
			}
		}

		_collider_oob.insert(_collider_oob.end(), out.begin(), out.end());

		// Collisions
		this->collide_all();
	}

	void PhysicsManager::collide_all()
	{
		std::map<Entity, std::vector<TriggerEvent>> triggers{};
		std::map<Entity, CollisionEvent> collisions{};

		for (auto it = _collider_all.begin(); it != _collider_all.end(); it++)
		{
			Entity entity_first = (*it)->get_entity();

			// Do not collide dead entities
			if (!entity_is_alive(entity_first))
			{
				it = _collider_all.erase(it);
				it--;
				continue;
			}

			BoundingBox box_first = (*it)->boundary + *entity_position(entity_first);
			BoundingBox search{ box_first.center, _range, _range };

			auto potential = _collider_tree.query_area(search);
			for (auto *other : potential)
			{
				Entity entity_second = other->get_entity();

				if (entity_first != entity_second && !entity_is_alive(entity_second))
				{
					continue;
				}

				BoundingBox box_second = other->boundary + *entity_position(entity_second);
				if (box_first.intersects(box_second))
				{
					if (other->trigger)
					{
						triggers[entity_first].push_back({ other->trigger, entity_second });
					}

					if ((*it)->layers & other->layers)
					{
						auto results = this->resolve_collision({ entity_first, (*it), box_first },
															   { entity_second, other, box_second });

						collisions[entity_first] |= results.first;
						collisions[entity_second] |= results.second;
					}
				}
			}
		}

		
		// TODO: Fire events
	}

	PhysicsManager::CollisionResult PhysicsManager::resolve_collision(CollisionPart first, CollisionPart second)
	{
		PhysicsManager::CollisionResult result{ 0, 0 };

		bool push_first = first.collider->blocked && second.collider->solid;
		bool push_second = first.collider->solid && second.collider->blocked;

		if (!(push_first || push_second)) // No interaction, we're done.
		{
			return result;
		}

		// TODO: Resolve platforms

		Vector2 layout = (second.derived.center - first.derived.center);
		// Offset is the necessary distance to push either entity to move it out of the other.
		Vector2 offset{ (first.derived.halfwidth + second.derived.halfwidth - std::abs(second.derived.center.x - first.derived.center.x)) * sign(layout.x),
						(first.derived.halfheight + second.derived.halfheight - std::abs(second.derived.center.y - first.derived.center.y)) * sign(layout.y)};
		if (push_first && push_second)
		{
			offset = offset / 2.0f;
		}

		if (std::abs(offset.x) <= std::abs(offset.y))
		{
			// Horizontal push
			if (push_first)
			{
				get_translation(first.entity)->position.x -= offset.x;
				// TODO: Add event
			}

			if (push_second)
			{
				get_translation(second.entity)->position.x += offset.x;
				// TODO: Add event
			}
		}
		else
		{
			// Vertical push
			if (push_first)
			{
				get_translation(first.entity)->position.y -= offset.y;
				// TODO: Add event
			}

			if (push_second)
			{
				get_translation(second.entity)->position.y += offset.y;
				// TODO: Add event
			}
		}


		return result;
	}
}
