#pragma once

#include "entitymanager.h"
#include "component.h"
#include "entityinterface.h"

#include <foundation\activatable.h>

#include <vector>
#include <map>
#include <memory>

namespace cookiejar
{
	class Translation;

	class ComponentManager : public Activatable<ComponentManager>
	{
	public:
		ComponentManager();
		~ComponentManager();

		template <typename T>
		inline std::vector<std::shared_ptr<Component>> get_components(const Entity &entity)
		{
			/*if (!EntityManager::is_alive())
			{
				return NULL;
			}*/
			return NULL;
		}


		void attach(const Entity &entity, std::shared_ptr<Component>);
		void detach(const Entity &entity, std::shared_ptr<Component>);

	private:
		std::map<Entity, std::vector<std::shared_ptr<Component>>> _generic_components;
	};
}
