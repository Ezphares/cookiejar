#pragma once

#include "physicsinterface.h"

#include <componentmodel\entity.h>
#include <foundation\quadtree.h>
#include <componentmodel\componentinterface.h>
#include <foundation\activatable.h>

#include <map>
#include <list>

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
		void attach_translation(const Entity &entity, std::shared_ptr<Translation> translation);
		std::shared_ptr<Translation> get_translation(const Entity &entity);

		void attach_collider(const Entity &entity, std::shared_ptr<Collider> collider);
		void detach_collider(const Entity &entity, std::shared_ptr<Collider> collider);
		std::vector<std::shared_ptr<Collider>> get_colliders(const Entity &entity);

		void update(BasePrecision delta);
		CollisionEvent physics_step(Collider *collider);

		bool is_free(const Entity &entity, Vector2 position, bool only_solid);

	private:
		void collide_all();
		CollisionResult resolve_collision(CollisionPart first, CollisionPart second);
		CollisionEvent push_vertical(CollisionPart pushed, CollisionPart pusher);
		CollisionEvent push_horizontal(CollisionPart pushed, CollisionPart pusher);

	private:
		std::list<std::shared_ptr<Collider>> _collider_all;

		QTree<std::shared_ptr<Collider>> _collider_tree;
		std::list<std::shared_ptr<Collider>> _collider_oob;

		std::vector<std::shared_ptr<Translation>> _translations;

		float _range;
	};

}
