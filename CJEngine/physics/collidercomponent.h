#pragma once

#include <componentmodel\componentinterface.h>

#include <foundation\boundingbox.h>
#include <foundation\vector.h>

namespace cookiejar
{
	class Collider : public Component
	{
		typedef std::uint32_t LayerMask;
		enum Platform {NO, UP, DOWN, LEFT, RIGHT};

	public:
		inline Collider(const BoundingBox &boundary = BoundingBox(), const Vector2 &offset = Vector2(), const LayerMask &layers = 1,
						const bool &solid = false, const bool &blocked = false, const bool &trigger = false, const Platform &platform = NO) :
			boundary(boundary),
			offset(offset),
			layers(layers),
			solid(solid),
			blocked(blocked),
			trigger(trigger),
			platform(platform)
		{}

	public:
		BoundingBox boundary;
		Vector2 offset;
		LayerMask layers;
		bool solid, blocked, trigger;
		Platform platform;
	};



	template <>
	inline Collider *component_get<Collider>(const Entity &entity)
	{
		return NULL;// TODO
	}

	template <>
	inline void component_attach<Collider>(const Entity &entity, const Collider &translation)
	{
		// TODO
	}

	template <>
	inline void component_detach<Collider>(const Entity &entity, const Collider &translation)
	{
		// TODO
	}

}
