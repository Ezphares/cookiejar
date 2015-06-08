#pragma once

#include "entitymanager.h"
#include "component.h"
#include "entityinterface.h"

#include <foundation\activatable.h>

#include <vector>
#include <map>

namespace cookiejar
{
	class Translation;

	class ComponentManager : public Activatable<ComponentManager>
	{
	private:
		ComponentManager();

	public:
		~ComponentManager();

		template <typename T>
		inline std::vector<Component *> get_components(const Entity &entity)
		{
			/*if (!EntityManager::is_alive())
			{
				return NULL;
			}*/
			return NULL;
		}


		void attach(const Entity &entity, Component *component);
		void detach(const Entity &entity, Component *component);
		std::vector<Translation> &get_translations();

	private:
		std::vector<Translation> _translations;
		std::map<Entity, std::vector<Component *>> _generic_components;
	};
}
