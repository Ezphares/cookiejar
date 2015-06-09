#include "componentmanager.h"

#include "translationcomponent.h"

#include <algorithm>

namespace cookiejar
{
	ComponentManager::ComponentManager() :
		_translations(),
		_generic_components()
	{
	}


	ComponentManager::~ComponentManager()
	{
	}

	std::vector<Translation> &ComponentManager::get_translations()
	{
		return _translations;
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
