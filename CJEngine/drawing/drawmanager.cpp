#include "drawmanager.h"

#include "drawcomponent.h"
#include <componentmodel/entity.h>
#include <componentmodel/entityinterface.h>

#include <algorithm>


namespace cookiejar
{
	DrawManager::DrawManager(GraphicsController *controller) :
		_controller(controller),
		_components()
	{
	}


	DrawManager::~DrawManager()
	{
	}

	void DrawManager::draw_sprite(Sprite *sprite, const int &frame, const Vector2 &position)
	{
		sprite->get_texture()->bind();
		_controller->draw_textured_rectangle(
			position,
			sprite->get_framesize(),
			sprite->get_offset(frame),
			sprite->get_size());
	}

	void DrawManager::attach(const Entity &entity, Draw *component)
	{
		_components.push_back(component);
	}

	void DrawManager::detach(const Entity &entity, Draw *component)
	{
		auto it = std::find(_components.begin(), _components.end(), component);
		if (it != _components.end())
		{
			_components.erase(it);
		}
	}

	std::vector<Draw *> DrawManager::get_by_entity(const Entity &entity)
	{
		std::vector<Draw *> result;
		for (auto draw : _components)
		{
			if (draw->get_entity() == entity)
			{
				result.push_back(draw);
			}
		}
		return result;
	}

	void DrawManager::draw_all(float delta)
	{
		std::sort(_components.begin(), _components.end(), depth_compare);

		_controller->draw_start();

		auto it = _components.begin();
		while (it != _components.end())
		{
			Draw *draw = (*it);
			Entity ent = draw->get_entity();
			if (!entity_is_alive(ent))
			{
				it = _components.erase(it);
				delete draw;
			}

			draw->script(ent, draw, (void *)(&delta));
			it++;
		}

		_controller->draw_end();
	}
}
