#pragma once

#include <window/glwindow.h>
#include "room.h"

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

		Room *create_room(bool activate = true);

	public:
		WindowSettings window_settings;
	
	private:
		GLWindow _window;
		bool _initialized;
		Room *_active_room;
	};
}
