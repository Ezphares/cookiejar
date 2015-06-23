#pragma once

#include <iostream>

namespace cookiejar
{

	template <typename T>
	struct Point
	{
		T x, y;

		// Used for bounding box placement
		inline Point<T> point()
		{
			return *this;
		}
	};

	/*
	 * Arithmetic operators
	 */
	template <typename T>
	inline Point<T> operator+(const Point<T> &lhs, const Point<T> &rhs)
	{
		return Point<T> {lhs.x + rhs.x, lhs.y + rhs.y};
	}

	template <typename T>
	inline Point<T> operator-(const Point<T> &lhs, const Point<T> &rhs)
	{
		return Point<T> {lhs.x - rhs.x, lhs.y - rhs.y};
	}

	template <typename T>
	inline Point<T> operator*(const Point<T> &lhs, const T &rhs)
	{
		return Point<T> {lhs.x * rhs, lhs.y * rhs};
	}

	template <typename T>
	inline Point<T> operator/(const Point<T> &lhs, const T &rhs)
	{
		return Point<T> {lhs.x / rhs, lhs.y / rhs};
	}

	// Memberwise multiplication and division
	template <typename T>
	inline Point<T> operator*(const Point<T> &lhs, const Point<T> &rhs)
	{
		return Point<T> {lhs.x * rhs.x, lhs.y * rhs.y};
	}

	template <typename T>
	inline Point<T> operator/(const Point<T> &lhs, const Point<T> &rhs)
	{
		return Point<T> {lhs.x / rhs.x, lhs.y / rhs.y};
	}

	// Point cast
	template <typename U, typename T>
	inline Point<U> point_cast(Point<T> org)
	{
		return Point<U> {static_cast<U>(org.x), static_cast<U>(org.y) };
	}

	/*
	 * Arithmetic assignment
	 */
	template <typename T>
	inline Point<T> operator+=(Point<T> &lhs, const Point<T> &rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	template <typename T>
	inline Point<T> operator-=(Point<T> &lhs, const Point<T> &rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	template <typename T>
	inline Point<T> operator*=(Point<T> &lhs, const T &rhs)
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		return lhs;
	}

	template <typename T>
	inline Point<T> operator/=(Point<T> &lhs, const T &rhs)
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		return lhs;
	}

	// Cout
	template <typename T>
	inline std::ostream &operator<<(std::ostream &stream, const Point<T> &point)
	{
		stream << '(' << point.x << ',' << point.y << ')';
		return stream;
	}

	typedef float BasePrecision;
	typedef Point<BasePrecision> Vector2;
}
