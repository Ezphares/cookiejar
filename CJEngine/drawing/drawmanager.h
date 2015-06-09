#pragma once

#include <foundation/activatable.h>
#include <componentmodel/component.h>

#include <window/graphics/glgraphicscontroller.h>
#include <window/graphics/sprite.h>

#include <vector>

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
		
		void attach(const Entity &entity, Draw *component);
		void detach(const Entity &entity, Draw *component);
		std::vector<Draw *> get_by_entity(const Entity &entity);

		void draw_all(float delta);

	private:
		GraphicsController *_controller;
		std::vector<Draw *> _components;
	};
}
