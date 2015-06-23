#pragma once

#include "drawinterface.h"
#include "drawmanager.h"

#include <componentmodel/componentinterface.h>
#include <componentmodel/component.h>
#include <foundation/functions.h>

namespace cookiejar
{
	class Draw : public Component
	{
	public:
		inline Draw(BehaviourScript script = NULL, int depth = 0) :
			script(script),
			depth(depth)
		{}

		BehaviourScript script;
		int depth;
	};


	inline bool depth_compare(std::shared_ptr<Draw> a, std::shared_ptr<Draw> b)
	{
		return b->depth < a->depth;
	}

	template <>
	inline std::vector<std::shared_ptr<Draw>> component_get_internal<Draw>(const Entity &entity)
	{
		return DrawManager::active()->get_by_entity(entity);
	}

	template <>
	inline void component_attach_internal<Draw>(const Entity &entity, std::shared_ptr<Draw> component)
	{
		DrawManager::active()->attach(entity, component);
	}

	template <>
	inline void component_detach_internal<Draw>(const Entity &entity, std::shared_ptr<Draw> component)
	{
		DrawManager::active()->detach(entity, component);
	}
}
