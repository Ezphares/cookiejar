#pragma once

#include "entitymanager.h"
#include "component.h"
#include "entityinterface.h"

#include <vector>
#include <map>

namespace cookiejar
{
	class Translation;

	class ComponentManager
	{
	private:
		ComponentManager();

	public:
		~ComponentManager();

		template <typename T>
		Component *get_component(const Entity &entity)
		{
			/*if (!EntityManager::is_alive())
			{
				return NULL;
			}*/
			return NULL;
		}

		std::vector<Translation> &get_translations();

	public:
		void activate();
		static ComponentManager *active();

	private:
		std::vector<Translation> translations;
		std::map<Entity, std::vector<Component>> generic_components;
		static ComponentManager *ACTIVE;
	};
}
