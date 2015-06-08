#pragma once

#include <componentmodel\entity.h>
#include <foundation\quadtree.h>
#include <componentmodel\componentinterface.h>
#include <componentmodel\translationcomponent.h>
#include <foundation\activatable.h>

#include <map>

namespace cookiejar
{
	class Collider;


	class PhysicsManager : public Activatable<PhysicsManager>
	{
	public:
		PhysicsManager(const BoundingBox &area);
		virtual ~PhysicsManager();

	public:
		void attach(const Entity &entity, Collider *collider);
		void detach(const Entity &entity, Collider *collider);
		Collider *get_by_entity(const Entity &entity);

	private:
		QTree<Collider *> _collider_tree;
		std::map<Entity, std::vector<Collider>> _collider_map;
	};

}
