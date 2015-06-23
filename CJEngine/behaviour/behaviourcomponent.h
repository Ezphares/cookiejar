#pragma once

#include "behaviourmanager.h"

#include <componentmodel/componentinterface.h>
#include <foundation/functions.h>

#include <memory>

namespace cookiejar
{
	class Behaviour : public Component
	{
	public:
		inline Behaviour() :
			init(nop), create(nop), update(nop), post_update(nop), destroy(nop)
		{}

		BehaviourScript init, // Called the first step that the component is attached to a new entity
						create, // Called the first step of the entity's life, if this behaviour is attached
						update, // Called each physics frame, before physics
						post_update, // Called each physics frame, after physics
						destroy;
	};


	template <>
	inline std::vector<std::shared_ptr<Behaviour>> component_get_internal<Behaviour>(const Entity &entity)
	{
		return BehaviourManager::active()->get_behaviours(entity);
	}

	template <>
	inline void component_attach_internal<Behaviour>(const Entity &entity, std::shared_ptr<Behaviour> behaviour)
	{
		BehaviourManager::active()->attach_behaviour(entity, behaviour);
	}

	template <>
	inline void component_detach_internal<Behaviour>(const Entity &entity, std::shared_ptr<Behaviour> behaviour)
	{
		BehaviourManager::active()->detach_behaviour(entity, behaviour);
	}
}
