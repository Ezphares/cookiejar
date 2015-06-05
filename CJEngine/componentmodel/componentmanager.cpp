#include "componentmanager.h"

#include "translationcomponent.h"

namespace cookiejar
{
	ComponentManager *ComponentManager::ACTIVE = NULL;


	ComponentManager::ComponentManager()
	{
	}


	ComponentManager::~ComponentManager()
	{
	}

	std::vector<Translation> &ComponentManager::get_translations()
	{
		return this->translations;
	}

	void ComponentManager::activate()
	{
		ComponentManager::ACTIVE = this;
	}

	ComponentManager *ComponentManager::active()
	{
		return ComponentManager::ACTIVE;
	}
}
