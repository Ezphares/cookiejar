#include <iostream>

#include "foundation/quadtree.h"
#include "componentmodel\translationcomponent.h"

using namespace cookiejar;

int main(int argc, char *argv[])
{
	Vector2 a{ 1, 2 };
	a += Vector2{ 1, 2 };

	BoundingBox bb{ Vector2{ 0, 0 }, 100.0, 100.0 };

	QuadTree q{ bb };
	std::cout << q.insert(a) << std::endl;
	return 0;
}
