#include "game.h"

#include <window\glwindow.h>
#include <window\graphics\glgraphicscontroller.h>
#include <window\graphics\sprite.h>

#include <stdexcept>

namespace cookiejar
{
	Game::Game() :
		window_settings(),
		_window(),
		_initialized(false),
		_active_room(NULL)
	{
	}


	Game::~Game()
	{
	}


	void Game::initialize()
	{
		if (_initialized)
			throw std::runtime_error("cookiejar::Game initialized twice.");

		_window.initialize();
		this->apply_settings();
		_initialized = true;
	}

	void Game::apply_settings()
	{
		_window.setup(window_settings);
	}

	void Game::run()
	{
		if (!_initialized)
			this->initialize();

		auto *input = _window.get_input_controller();

		while (_window.is_running())
		{
			input->update();
			input->retrieve_events();
			input->clear_events();

			if (_active_room)
			{
				_active_room->draw(0.0);
			}
			else
			{
				auto *gfx = _window.get_graphics_controller();
				gfx->draw_start();
				gfx->draw_end();
			}
		}
	}

	Room *Game::create_room(bool activate)
	{
		_active_room = new Room(_window.get_graphics_controller(), BoundingBox{ Vector2{ 0, 0 }, 400, 300 });

		if (activate)
		{
			_active_room->activate_all();
		}

		return _active_room;
	}
}
