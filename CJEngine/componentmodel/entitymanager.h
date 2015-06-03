#pragma once

#include "entity.h"

#include <vector>
#include <queue>

namespace cookiejar
{
	const uint32_t ENTITY_INDEX_REUSE_DELAY = 1024;


	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

	public:
		Entity create_entity();
		void destroy_entity(const Entity &entity);
		bool is_alive(const Entity &entity) const;

	private:
		std::vector<Entity> _entities;
		std::queue<uint32_t> _indices;
	};
}
