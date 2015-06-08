#pragma once

#include <componentmodel\componentinterface.h>
#include <componentmodel\translationcomponent.h>
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
		inline Collider(const BoundingBox &boundary = BoundingBox(), const Vector2 &offset = Vector2(), const LayerMask &layers = 1,
						const bool &solid = false, const bool &blocked = false, const bool &trigger = false, const Platform &platform = NO) :
			boundary(boundary),
			offset(offset),
			layers(layers),
			solid(solid),
			blocked(blocked),
			trigger(trigger),
			platform(platform)
		{}

	public:
		BoundingBox boundary;
		Vector2 offset;
		LayerMask layers;
		bool solid, blocked, trigger;
		Platform platform;
	};

	template <>
	inline Vector2 get_qtree_vector<Collider *>(Collider * const &collider)
	{
		const Entity &e = collider->get_entity();
		Translation *trans = component_get<Translation>(e);
		return Vector2{ collider->offset.x + trans->pos.x, collider->offset.y + trans->pos.y };
	}


	template <>
	inline Collider *component_get<Collider>(const Entity &entity)
	{
		return PhysicsManager::active()->get_by_entity(entity);
	}

	template <>
	inline void component_attach_internal<Collider>(const Entity &entity, Collider *collider)
	{
		PhysicsManager::active()->attach(entity, collider);
	}

	template <>
	inline void component_detach<Collider>(const Entity &entity, Collider *collider)
	{
		PhysicsManager::active()->detach(entity, collider);
	}

}
