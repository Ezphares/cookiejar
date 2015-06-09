#include <iostream>

#include "foundation/quadtree.h"
#include "componentmodel\translationcomponent.h"
#include "window\glwindow.h"
#include "window\graphics\glgraphicscontroller.h"
#include <GLFW\glfw3.h>

using namespace cookiejar;

int main(int argc, char *argv[])
{
	GLWindow window;
	WindowSettings settings = {};
	settings.resolution = { 800, 600 };
	settings.caption = "Test";
	settings.fullscreen = false;


	try
	{
		window.initialize();
		window.setup(settings);
	}
	catch (int i)
	{
		std::cout << i << std::endl;
	}

	while (true);
	
	//Vector2 a{ 1, 2 };
	//a += Vector2{ 1, 2 };

	//BoundingBox bb{ Vector2{ 0, 0 }, 100.0, 100.0 };

	//QuadTree q{ bb };
	//std::cout << q.insert(a) << std::endl;
	return 0;
}
