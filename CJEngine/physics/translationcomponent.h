#pragma once

#include "physicsmanager.h"

#include <componentmodel\componentinterface.h>
#include <foundation\vector.h>

#include <iostream>

namespace cookiejar
{
	class Translation : public Component
	{
	public:
		inline Translation(const Vector2 &pos = Vector2{ 0, 0 }, const Vector2 &velocity = Vector2{ 0, 0 }) :
			position(pos),
			position_previous(pos),
			position_initial(pos),
			velocity(velocity)
		{}

	public:
		Vector2 position, position_previous, position_initial, velocity;
	};



	template <>
	inline std::vector<Translation *> component_get_internal<Translation>(const Entity &entity)
	{
		std::vector<Translation *> result{};
		if (entity_is_alive(entity))
		{
			result.push_back(PhysicsManager::active()->get_translation(entity));
		}
		return result;
	}

	template <>
	inline void component_attach_internal<Translation>(const Entity &entity, Translation *translation)
	{
		if (!entity_is_alive(entity)) // TODO Assert instead?
			return;

		PhysicsManager::active()->attach_translation(entity, translation);
	}

	template <>
	inline void component_detach_internal<Translation>(const Entity &entity, Translation *translation)
	{
		return; // Never detach translations
	}
}
