#pragma once

#include "componentinterface.h"

#include <foundation\vector.h>

namespace cookiejar
{
	class Translation : public Component
	{
	public:
		inline Translation(Vector2 pos = Vector2()) :
			pos(pos)
		{}

	public:
		Vector2 pos;
	};



	template <>
	inline std::vector<Translation *> component_get_internal<Translation>(const Entity &entity)
	{
		std::vector<Translation *> result;
		if (!entity_is_alive(entity))
			return result;

		std::vector<Translation> &list = ComponentManager::active()->get_translations();
		result.push_back(&list[entity.index()]);
		return result;
	}

	template <>
	inline void component_attach_internal<Translation>(const Entity &entity, Translation *translation)
	{
		if (!entity_is_alive(entity)) // TODO Assert instead?
			return;

		std::vector<Translation> &list = ComponentManager::active()->get_translations();
		auto index = entity.index();
		while (list.size() < index)
		{
			list.push_back(Translation());
		}

		list[index] = *translation;
	}

	template <>
	inline void component_detach_internal<Translation>(const Entity &entity, Translation *translation)
	{
		return; // Never detach translations
	}

}
