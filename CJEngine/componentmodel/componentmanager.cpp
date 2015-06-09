#include "componentmanager.h"

#include <algorithm>

namespace cookiejar
{
	ComponentManager::ComponentManager() :
		_generic_components()
	{
	}


	ComponentManager::~ComponentManager()
	{
	}

	void ComponentManager::attach(const Entity &entity, Component *component)
	{
		_generic_components[entity].push_back(component);
	}

	void ComponentManager::detach(const Entity &entity, Component *component)
	{
		auto &list = _generic_components[entity];

		auto it = std::find(list.begin(), list.end(), component);
		if (it != list.end())
		{
			list.erase(it);
		}
	}
}
