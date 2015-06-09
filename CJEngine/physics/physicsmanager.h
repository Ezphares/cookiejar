#pragma once

#include <componentmodel\entity.h>
#include <foundation\quadtree.h>
#include <componentmodel\componentinterface.h>
#include <foundation\activatable.h>

#include <map>

namespace cookiejar
{
	class Collider;
	class Translation;


	class PhysicsManager : public Activatable<PhysicsManager>
	{
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

	private:
		QTree<Collider *> _collider_tree;
		std::map<Entity, std::vector<Collider>> _collider_map;
		std::vector<Translation *> _translations;
	};

}
