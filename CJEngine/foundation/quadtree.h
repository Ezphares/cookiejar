#pragma once

#include "boundingbox.h"

#include <type_traits>
#include <cstdint>
#include <vector>

#include <iostream>

namespace cookiejar
{
	template <typename T>
	inline Vector2 get_qtree_vector(const T &object)
	{
		static_assert(sizeof(T) == -1, "To use type T in a QTree, specialize get_qtree_vector<T>");
		return Vector2{ 0, 0 };
	}

	template <>
	inline Vector2 get_qtree_vector<Vector2>(const Vector2 &object)
	{
		return object;
	}

	template <>
	inline Vector2 get_qtree_vector<Vector2 *>(Vector2 * const &object)
	{
		return *object;
	}

	/*
	 * Basic quadtree
	 */
	template <typename T>
	class QTree
	{
	private:
		typedef std::integral_constant<std::size_t, 4> CAPACITY;

	public:
		inline QTree(const BoundingBox &boundary) :
			_boundary(boundary),
			_elements(),
			_branches()
		{};

		inline virtual ~QTree()
		{
			for (std::size_t i = 0; i < 4; ++i)
			{
				delete _branches[i];
			}
		}

		inline bool insert(const T &element)
		{
			return this->insert_point(element, get_qtree_vector<T>(element));
		}

		inline void remove(const T &element)
		{
			this->remove_point(element, get_qtree_vector<T>(element));
		}

		inline std::vector<T> list()
		{
			this->query_area(this->boundary);
		}

		std::vector<T> query_area(BoundingBox &area)
		{
			std::vector<T> result;

			if (!_boundary.intersects(area))
			{
				return result;
			}

			for (auto element : _elements)
			{
				if (area.contains(get_qtree_vector(element)))
				{
					result.push_back(element);
				}
			}

			if (!_branches[0])
			{
				return result;
			}

			std::size_t t_size = result.size();
			std::vector<T> c_lists[4] = {};

			for (std::size_t i = 0; i < 4; ++i)
			{
				c_lists[i] = _branches[i]->query_area(area);
				t_size += c_lists[i].size();
			}

			result.reserve(t_size);
			for (std::size_t i = 0; i < 4; ++i)
			{
				result.insert(result.end(), c_lists[i].begin(), c_lists[i].end());
			}

			return result;
		}

		/*
		 * If any point can be moved around, call update to restructure the tree.
		 * A vector of all elements no longer within the boundary is returned.
		 */
		std::vector<T> update()
		{
			std::vector<T> result;

			// Recursively create a list of returned elements from children
			std::size_t t_size = QTree<T>::CAPACITY::value;
			if (_branches[0])
			{
				std::vector<T> c_lists[4] = {};

				for (std::size_t i = 0; i < 4; ++i)
				{
					c_lists[i] = _branches[i]->update();
					t_size += c_lists[i].size();
				}

				result.reserve(t_size);
				for (std::size_t i = 0; i < 4; ++i)
				{
					result.insert(result.end(), c_lists[i].begin(), c_lists[i].end());
				}
			}
			else
			{
				result.reserve(t_size);
			}

			// Attempt to insert returned children
			auto it = result.begin();
			while (it != result.end())
			{
				Vector2 point = get_qtree_vector(*it);
				if (insert_point(*it, point))
				{
					it = result.erase(it);
					continue;
				}
				++it;
			}

			// Add own children if necessary
			auto jt = _elements.begin();
			while (jt != _elements.end())
			{
				Vector2 point = get_qtree_vector(*jt);
				if (!_boundary.contains(point))
				{
					result.push_back(*jt);
					jt = _elements.erase(jt);
					continue;
				}
				++jt;
			}
			return result;
		}

	private:
		bool insert_point(const T &element, const Vector2 &point)
		{
			// Does the obejct fit in this node?
			if (!_boundary.contains(point))
			{
				return false;
			}

			// Is there space in this node?
			if (_elements.size() < QTree<T>::CAPACITY::value)
			{
				_elements.push_back(element);
				return true;
			}

			// Do we need to subdivide?
			if (!_branches[0])
			{
				this->subdivide();
			}


			// Attempt insertion in branches!
			for (std::size_t i = 0; i < 4; ++i)
			{
				if (_branches[i]->insert_point(element, point)) return true;
			}

			// If this happens, something has gone horribly wrong
			return false;
		}

		void remove_point(const T &element, const Vector2 &point)
		{
			if (!_boundary.contains(point))
			{
				return;
			}

			for (auto it = _elements.begin(); it < _elements.end(); ++it)
			{
				if (*it == element)
				{
					_elements.erase(it);
					return;
				}
			}

			for (std::size_t i = 0; i < 4; ++i)
			{
				_branches[i]->remove_point(element, point);
			}
		}
		
		void subdivide()
		{
			float w = _boundary.halfwidth / 2,
				  h = _boundary.halfheight / 2;

			// Create subdivision boxes
			BoundingBox
				tl{ (_boundary.center - Vector2{ w, h }), w, h },
				tr = tl + Vector2{ _boundary.halfwidth, 0 },
				bl = tl + Vector2{ 0, _boundary.halfheight },
				br = bl + Vector2{ _boundary.halfwidth, 0 };

			_branches[0] = new QTree<T>(tl);
			_branches[1] = new QTree<T>(tr);
			_branches[2] = new QTree<T>(bl);
			_branches[3] = new QTree<T>(br);
		}

	private:
		BoundingBox _boundary;
		std::vector<T> _elements;
		QTree<T> *_branches[4];
	};

	typedef QTree<Vector2> QuadTree;
}
