#pragma once

#include "physicsinterface.h"

#include <componentmodel\entity.h>
#include <foundation\quadtree.h>
#include <componentmodel\componentinterface.h>
#include <foundation\activatable.h>

#include <map>
#include <deque>

namespace cookiejar
{
	class Collider;
	class Translation;


	class PhysicsManager : public Activatable<PhysicsManager>
	{
		struct CollisionResult
		{
			CollisionEvent first, second;
		};

		struct CollisionPart
		{
			Entity entity;
			Collider *collider;
			BoundingBox derived;
		};

	public:
		PhysicsManager(const BoundingBox &area);
		virtual ~PhysicsManager();

	public:
		void attach_translation(const Entity &entity, Translation *translation);
		Translation *get_translation(const Entity &entity);

		void attach_collider(const Entity &entity, Collider *collider);
		void detach_collider(const Entity &entity, Collider *collider);
		Collider *get_collider(const Entity &entity);

		void update(float delta);
		CollisionEvent physics_step(Collider *collider);

	private:
		void collide_all();
		CollisionResult resolve_collision(CollisionPart first, CollisionPart second);

	private:
		std::deque<Collider *> _collider_all;

		QTree<Collider *> _collider_tree;
		std::vector<Collider *> _collider_oob;

		std::vector<Translation *> _translations;

		float _range;
	};

}
