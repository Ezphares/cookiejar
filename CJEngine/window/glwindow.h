#pragma once

#include "graphics/glgraphicscontroller.h"
#include "input/glinputcontroller.h"
#include "windowsettings.h"

namespace cookiejar
{
#ifdef USE_GL_RENDERER
	typedef GLGraphicsController GraphicsController;
	typedef GLInputController InputController;
#endif

	class GLWindow
	{
	public:
		GLWindow();
		~GLWindow();

		void initialize();
		void setup(const WindowSettings &settings);
		void terminate();

		GraphicsController *get_graphics_controller();
		InputController *get_input_controller();

		bool is_running();

	private:
		bool _ready, _initialized;
		WindowType *_window;
		GraphicsController _graphics_controller;
		InputController _input_controller;
		WindowSettings _settings;
	};

#ifdef USE_GL_RENDERER
	typedef GLWindow Window;
#endif
	
}
