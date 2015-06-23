#pragma once

#include <foundation/activatable.h>
#include <componentmodel/component.h>

#include <window/graphics/glgraphicscontroller.h>
#include <window/graphics/sprite.h>

#include <list>
#include <vector>
#include <memory>

namespace cookiejar
{
	class Draw;

	class DrawManager : public Activatable<DrawManager>
	{
	public:
		DrawManager(GraphicsController *controller);
		~DrawManager();

	public:
		void draw_sprite(Sprite *sprite, const int &frame, const Vector2 &position);
		
		void attach(const Entity &entity, std::shared_ptr<Draw> component);
		void detach(const Entity &entity, std::shared_ptr<Draw> component);
		std::vector<std::shared_ptr<Draw>> get_by_entity(const Entity &entity);

		void draw_all(BasePrecision delta);

	private:
		GraphicsController *_controller;
		std::list<std::shared_ptr<Draw>> _components;
	};
}
