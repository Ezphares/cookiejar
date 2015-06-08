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

	template<typename T>
	void component_attach_internal(const Entity &entity, const T &cmp)
	{
		// ComponentManager::active()->attach(entity, component);
	}

	template<typename T>
	void component_detach_internal(const Entity &entity, const T &cmp)
	{
		// ComponentManager::active()->detach(entity, component);
	}



	template <typename T>
	void component_attach(const Entity &entity, const T &cmp)
	{
		Component &component = dynamic_cast<Component &>(cmp); // Throw std::bad_cast if not a component
		component.set_entity(entity);

		component_attach_internal<T>(entity, cmp);
	}

	template <typename T>
	void component_detach(const Entity &entity, const T &cmp)
	{
		Component &component = dynamic_cast<Component &>(cmp); // Throw std::bad_cast if not a component
		component.set_entity(Entity::none());
		component_detach_internal<T>(entity, cmp);
	}

}
