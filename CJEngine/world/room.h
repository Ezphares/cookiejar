#pragma once

#include <componentmodel/entitymanager.h>
#include <componentmodel/componentmanager.h>
#include <drawing/drawmanager.h>
#include <physics/physicsmanager.h>

#include <foundation/boundingbox.h>

namespace cookiejar
{
	class Room
	{
	public:
		Room(GraphicsController *gfx_controller, const BoundingBox &boundary);
		~Room();

	public:
		void update(float delta);
		void draw(float delta);
		void activate_all();

	private:
		EntityManager _entity_manager;
		ComponentManager _component_manager;
		DrawManager _draw_manager;
		PhysicsManager _physics_manager;
	};
}
