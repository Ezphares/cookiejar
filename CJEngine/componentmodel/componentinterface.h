#pragma once

#include "componentmanager.h"

#include <foundation\vector.h>

#include <vector>
#include <stdexcept>

namespace cookiejar
{
	struct Entity;

	/*
	* Specialize these templates for any components not in the generic list.
	* I.E. Specialize for all component types if possible, if any performance is needed
	*/
	template<typename T>
	void component_attach_internal(const Entity &entity, T *component)
	{
		ComponentManager::active()->attach(entity, &component);
	}

	template<typename T>
	void component_detach_internal(const Entity &entity, T *component)
	{
		ComponentManager::active()->detach(entity, &component);
	}

	template<typename T>
	std::vector<T *> component_get_internal(const Entity &entity)
	{
		return ComponentManager::active()->get_components<T>(entity);
	}

	/*
	 * End of specialization stuff
	 */

	template <typename T>
	T *component_get(const Entity &entity)
	{
		std::vector<T *> list = component_get_internal<T>(entity);

		if (list.size() != 1)
		{
			throw std::runtime_error( "\"component_get\" returned a number of components other than 1. Use \"component_get_all\" instead.");
		}

		return list[0];
	}

	template <typename T>
	std::vector<T *> component_get_all(const Entity &entity)
	{
		return component_get_internal<T>(entity);
	}

	template <typename T>
	void component_attach(const Entity &entity, T *component)
	{
		Component *cmp = dynamic_cast<Component *>(component); // Throw std::bad_cast if not a component
		cmp->set_entity(entity);

		component_attach_internal<T>(entity, component);
	}

	template <typename T>
	void component_detach(const Entity &entity, T *component)
	{
		Component *cmp = dynamic_cast<Component *>(component); // Throw std::bad_cast if not a component
		cmp->set_entity(Entity::none());

		component_detach_internal<T>(entity, component);
	}
}
