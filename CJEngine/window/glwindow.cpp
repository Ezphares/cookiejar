#include "glwindow.h"

#include "windowsettings.h"
#include <iostream>

namespace cookiejar
{
	GLWindow::GLWindow() : _ready(false), _initialized(false), _window(NULL), _settings() { }
	GLWindow::~GLWindow() { }

	void GLWindow::initialize()
	{
		// Initialize GLFW
		if (!_initialized && glfwInit())
		{
			_initialized = true;
			_graphics_controller.initialize();
		}
		else
		{
			throw 1; //TODO WindowException
		}
	}

	void GLWindow::setup(const WindowSettings &settings)
	{
		if (!_initialized)
		{
			throw 1; //TODO WindowException
		}

		_settings = settings;
		
		Point<uint32_t> size = { 640, 480 };
		if (settings.size.x && settings.size.y)
		{
			size = settings.size;
		}

		
		Point<uint32_t> resolution = size;
		if (settings.resolution.x && settings.resolution.y)
		{
			resolution = settings.resolution;
		}

		
		GLFWmonitor *monitor = settings.fullscreen ? glfwGetPrimaryMonitor() : NULL;
		
		if (_window)
		{
			glfwDestroyWindow(_window);
		}
		
		//glfwWindowHint(GLFW_RESIZABLE, 0);

		_window = glfwCreateWindow(size.x, size.y, settings.caption.c_str(), monitor, NULL);
		if (!_window)
		{
			glfwTerminate();
			throw 2; //TODO WindowException
		}
		glfwMakeContextCurrent(_window);
		
		glewInit();

		_graphics_controller.post_window_setup(_window, resolution);
		_input_controller.post_window_setup(_window, point_cast<float>(resolution) / point_cast<float>(size)); //TODO: Calculate real factor
		_ready = true;
	}

	void GLWindow::terminate()
	{
		if (_initialized)
		{
			glfwTerminate();
			_initialized = false;
			_ready = false;
		}
	}

	GraphicsController *GLWindow::get_graphics_controller()
	{
		if (!_ready)
		{
			return NULL;
		}

		return &_graphics_controller;
	}

	InputController *GLWindow::get_input_controller()
	{
		if (!_ready)
		{
			return NULL;
		}

		return &_input_controller;
	}

	bool GLWindow::is_running()
	{
		return (_window && !glfwWindowShouldClose(_window));
	}
}
