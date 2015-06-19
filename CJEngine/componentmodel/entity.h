#pragma once

#include <foundation/vector.h>

#include <cstdint>

namespace cookiejar
{
	const std::size_t ENTITY_GENERATION_BITS = 8;
	const std::size_t ENTITY_INDEX_BITS = 32 - ENTITY_GENERATION_BITS;
	const std::uint32_t ENTITY_GENERATION_MASK = ((1 << ENTITY_GENERATION_BITS) - 1) << ENTITY_INDEX_BITS;
	const std::uint32_t ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;

	struct Entity
	{
		std::uint8_t generation() const { return static_cast<std::uint8_t>((id & ENTITY_GENERATION_MASK) >> ENTITY_INDEX_BITS); }
		std::uint32_t index() const { return id & ENTITY_INDEX_MASK; }

		static inline Entity create(std::uint8_t generation, std::uint32_t index) { return Entity{ generation << 24 | index }; }
		static inline Entity none() { return Entity{ (std::uint32_t)-1 }; }

		std::uint32_t id;
	};

	inline bool operator< (const Entity &left, const Entity &right)
	{
		return left.id < right.id;
	}

	inline bool operator== (const Entity &left, const Entity &right)
	{
		return left.id == right.id;
	}

	inline bool operator!= (const Entity &left, const Entity &right)
	{
		return !(left == right);
	}
}
