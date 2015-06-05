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
	inline Translation *component_get<Translation>(const Entity &entity)
	{
		if (!entity_is_alive(entity))
			return NULL;

		std::vector<Translation> &list = ComponentManager::active()->get_translations();
		return &list[entity.index()];
	}

	template <>
	inline void component_attach<Translation>(const Entity &entity, const Translation &translation)
	{
		if (!entity_is_alive(entity)) // TODO Assert instead?
			return;

		std::vector<Translation> &list = ComponentManager::active()->get_translations();
		auto index = entity.index();
		while (list.size() < index)
		{
			list.push_back(Translation());
		}

		list[index] = translation;
	}

	template <>
	inline void component_detach<Translation>(const Entity &entity, const Translation &translation)
	{
		return; // Never detach translations
	}

}
