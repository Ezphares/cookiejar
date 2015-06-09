#include "entitymanager.h"

#include <iostream>

namespace cookiejar
{
	EntityManager::EntityManager() : 
		_entities(),
		_indices()
	{}


	EntityManager::~EntityManager()
	{}

	Entity EntityManager::create_entity()
	{
		Entity entity;
		std::uint32_t index = static_cast<std::uint32_t>(_entities.size());
		if (_indices.size() >= ENTITY_INDEX_REUSE_DELAY)
		{
			index = _indices.front();
			_indices.pop();
			entity = _entities[index];
		}
		else
		{
			entity = Entity::create(0, index);
			_entities.push_back(entity);
		}
		return entity;
	}

	void EntityManager::destroy_entity(const Entity &entity)
	{
		if (is_alive(entity))
		{
			std::uint32_t index = entity.index();
			std::uint8_t generation = entity.generation();

			_entities[index] = Entity::create(generation + 1, index);
			_indices.push(index);
		}
	}

	bool EntityManager::is_alive(const Entity &entity) const
	{
		return (_entities[entity.index()].generation() == entity.generation());
	}
}
