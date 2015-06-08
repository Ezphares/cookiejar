#pragma once

#include <cstdint>

namespace cookiejar
{
	typedef std::uint16_t ComponentType;
	struct Entity;

	class Component
	{
	public:
		inline Component(Entity entity = Entity::none()) :
			_entity(entity){};
		virtual inline ~Component()
		{}

		inline Entity get_entity()
		{
			return _entity;
		}

		inline void set_entity(const Entity &entity)
		{
			_entity = entity;
		}

	protected:
		Entity _entity;
	};
}
