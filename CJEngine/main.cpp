#include <iostream>

#include "quadtree.h"

using namespace cookiejar;
/*
namespace cookiejar
{
	template<>
	Vector2 get_qtree_vector<int>(const int &object)
	{
		return Vector2{ 0, 0 };
	}
}
*/

int main(int argc, char *argv[])
{
	Vector2 a{ 1, 2 };
	a += Vector2{ 1, 2 };

	BoundingBox bb{ Vector2{ 0, 0 }, 100.0, 100.0 };

	QuadTree q{ bb };
	QTree<int> qi{ bb };
	qi.insert(1);
	std::cout << q.insert(a) << std::endl;
	return 0;
}
