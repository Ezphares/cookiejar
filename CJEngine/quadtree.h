#pragma once

#include <type_traits>
#include <cstdint>

#include "boundingbox.h"

#include <vector>

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


	template <typename T>
	class QTree
	{
	private:
		typedef std::integral_constant<std::uint16_t, 4> CAPACITY;

	public:
		inline QTree(BoundingBox &boundary, QTree *parent = NULL) :
			boundary(boundary),
			elements(),
			parent(parent),
			branches()
		{};

		inline virtual ~QTree()
		{
			for (std::size_t i = 0; i < 4; ++i)
			{
				delete this->branches[i];
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

		std::vector<T*> query_area(BoundingBox &area); // TODO Implement

	public: // DEBUG
		bool insert_point(const T &element, const Vector2 &point)
		{
			if (!this->boundary.contains(point))
			{
				return false; // Out of bounds
			}

			if (this->elements.size() < QTree<T>::CAPACITY::value)
			{
				this->elements.push_back(element);
			}

			if (!this->branches[0])
			{
				this->subdivide();
			}

			for (std::size_t i = 0; i < 4; ++i)
			{
				if (this->branches[i]->insert_point(element, point)) return true;
			}

			return false;
		}

		void remove_point(const T &element, const Vector2 &point)
		{
			if (!this->boundary.contains(point))
			{
				return;
			}

			for (auto it = this->elements.begin(); it < this->elements.end(); ++it)
			{
				if (*it == element)
				{
					this->elements.erase(it);
					return;
				}
			}

			for (std::size_t i = 0; i < 4; ++i)
			{
				this->branches[i]->remove_point(element, point);
			}
		}
		
		void subdivide()
		{
			float w = this->boundary.halfwidth / 2,
				  h = this->boundary.halfheight / 2;

			BoundingBox
				tl{ (this->boundary.center - Vector2{ w, h }), w, h },
				tr = tl + Vector2{ this->boundary.halfwidth, 0 },
				bl = tl + Vector2{ 0, this->boundary.halfheight },
				br = bl + Vector2{ this->boundary.halfwidth, 0 };

			this->branches[0] = new QTree<T>(tl, this);
			this->branches[1] = new QTree<T>(tr, this);
			this->branches[2] = new QTree<T>(bl, this);
			this->branches[3] = new QTree<T>(br, this);
		}

	public: // DEBUG
		BoundingBox boundary;
		std::vector<T> elements;
		QTree<T> *parent;
		QTree<T> *branches[4];
	};

	typedef QTree<Point<float>> QuadTree;
}
