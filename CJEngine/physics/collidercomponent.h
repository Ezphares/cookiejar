#pragma once

#include <componentmodel\componentinterface.h>
#include "translationcomponent.h"
#include <foundation\quadtree.h>

#include <foundation\boundingbox.h>
#include <foundation\vector.h>
#include "physicsmanager.h"

namespace cookiejar
{

	class Collider : public Component
	{
		typedef std::uint32_t LayerMask;
		enum Platform {NO, UP, DOWN, LEFT, RIGHT};

	public:
		inline Collider(const BoundingBox &boundary = BoundingBox(), const LayerMask &layers = 1,
						const bool &solid = false, const bool &blocked = false, const TriggerType &trigger = NOT_TRIGGER, const Platform &platform = NO) :
			boundary(boundary),
			layers(layers),
			solid(solid),
			blocked(blocked),
			trigger(trigger),
			platform(platform)
		{}

	public:
		BoundingBox boundary;
		LayerMask layers;
		bool solid, blocked;
		TriggerType trigger;
		Platform platform;
	};

	template <>
	inline Vector2 get_qtree_vector<Collider *>(Collider * const &collider)
	{
		const Entity &e = collider->get_entity();
		Translation *trans = component_get<Translation>(e);
		return collider->boundary.center + trans->position;
	}


	template <>
	inline Collider *component_get<Collider>(const Entity &entity)
	{
		return PhysicsManager::active()->get_collider(entity);
	}

	template <>
	inline void component_attach_internal<Collider>(const Entity &entity, Collider *collider)
	{
		PhysicsManager::active()->attach_collider(entity, collider);
	}

	template <>
	inline void component_detach<Collider>(const Entity &entity, Collider *collider)
	{
		PhysicsManager::active()->detach_collider(entity, collider);
	}

}
