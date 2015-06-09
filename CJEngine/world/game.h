#pragma once

#include <window/glwindow.h>

namespace cookiejar
{
	class Game
	{
	public:
		Game();
		~Game();

		void apply_settings();
		void initialize();
		void run();

	public:
		WindowSettings window_settings;
	
	private:
		GLWindow _window;
		bool _initialized;
	};
}
