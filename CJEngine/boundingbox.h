#pragma once

#include <cmath>

#include "vector.h"

namespace cookiejar
{
	template <typename T>
	struct AABB
	{
		Point<T> center;
		T halfwidth, halfheight;

		inline bool contains(const Point<T> &point) const
		{
			return (point.x >= this->center.x - halfwidth && point.x < this.center.x + halfwidth &&
				    point.y >= this->center.y - halfheight && point.y < this.center.y + halfheight)
		}

		inline bool intersects(const AABB<T> &other) const
		{
			Point<T> distance = this->center - other.center;
			Point<T> overlap{ this->halfwidth + other.halfwidth, this->halfheight + other.halfheight };
			return (std::abs(distance.x) < overlap.x && std::abs(distance.y) < overlap.y);
		}
	};

	/*
	 * Arithmetic operators
	 */
	template <typename T>
	inline AABB<T> operator+(const AABB<T> &lhs, const Point<T> &rhs)
	{
		return AABB<T> {lhs.center + rhs, lhs.halfwidth, lhs.halfheight};
	}

	template <typename T>
	inline AABB<T> operator-(const AABB<T> &lhs, const Point<T> &rhs)
	{
		return AABB<T> {lhs.center - rhs, lhs.halfwidth, lhs.halfheight};
	}

	/*
	 * Arithmetic assignment
	 */
	template <typename T>
	inline AABB<T> operator+=(AABB<T> &lhs, const Point<T> &rhs)
	{
		lhs.center += rhs;
		return lhs;
	}

	template <typename T>
	inline AABB<T> operator-=(AABB<T> &lhs, const Point<T> &rhs)
	{
		lhs.center -= rhs;
		return lhs;
	}


	typedef AABB<float> BoundingBox;
}
