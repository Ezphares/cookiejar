#pragma once

#include "componentmanager.h"

#include <foundation\vector.h>

namespace cookiejar
{
	struct Entity;


	template <typename T>
	T *component_get(const Entity &entity)
	{
		return ComponentManager::active()->get_component<T>(entity);
	}

	template <typename T>
	void component_attach(const Entity &entity, const T &cmp)
	{
		dynamic_cast<Component &>(cmp); // Throw std::bad_cast if not a component

		// ComponentManager::active()->attach(entity, component);
	}

	template <typename T>
	void component_detach(const Entity &entity, const T &cmp)
	{
		dynamic_cast<Component &>(cmp); // Throw std::bad_cast if not a component

		// ComponentManager::active()->detach(entity, component);
	}

}
