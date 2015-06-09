#include "room.h"


namespace cookiejar
{
	Room::Room(GraphicsController *gfx_controller, const BoundingBox &boundary) :
		_entity_manager(),
		_component_manager(),
		_draw_manager(gfx_controller),
		_physics_manager(boundary)
	{
	}

	Room::~Room()
	{
	}

	void Room::update(float delta)
	{
		this->activate_all();

		// TODO: Behaviour creations
		// TODO: Behaviour prestep
		_physics_manager.update(delta);
		// TODO: Behaviour poststep

	}

	void Room::draw(float delta)
	{
		this->activate_all();

		_draw_manager.draw_all(delta);
	}

	void Room::activate_all()
	{
		_entity_manager.activate();
		_component_manager.activate();
		_draw_manager.activate();
		_physics_manager.activate();
	}
}
