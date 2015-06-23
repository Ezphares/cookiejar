#include "room.h"


namespace cookiejar
{
	Room::Room(GraphicsController *gfx_controller, InputController *input_controller, const BoundingBox &boundary) :
		_entity_manager(),
		_component_manager(),
		_draw_manager(gfx_controller),
		_physics_manager(boundary),
		_behaviour_manager()
	{
	}

	Room::~Room()
	{
	}

	void Room::update(double delta)
	{
		this->activate_all();

		_behaviour_manager.update(delta);
		_physics_manager.update(delta);
		_behaviour_manager.post_update(delta);

	}

	void Room::draw(double delta)
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
		_behaviour_manager.activate();
	}
}
