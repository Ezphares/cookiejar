#include "game.h"

#include <window\glwindow.h>
#include <window\graphics\glgraphicscontroller.h>
#include <window\graphics\sprite.h>

#include <stdexcept>
#include <Windows.h>

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

		std::uint64_t steps = 0, last = this->get_tick();
		std::uint64_t physics_rate = 100;

		while (_window.is_running())
		{
			std::uint64_t now = this->get_tick();
			std::uint64_t ticks = now - last;
			last = now;
			steps += ticks;

			while (steps >= 1000 / physics_rate)
			{
				steps -= 1000 / physics_rate;
				if (_active_room)
				{
					float physics_delta = 1.0 / static_cast<float>(physics_rate);
					_active_room->update(physics_delta);
				}
			}

			if (_active_room)
			{
				float spf = static_cast<float>(ticks) / 1000.0;
				_active_room->draw(spf);
			}
			else
			{
				auto *gfx = _window.get_graphics_controller();
				gfx->draw_start();
				gfx->draw_end();
			}

			input->update();
			input->retrieve_events();
			input->clear_events();
		}
	}

	std::uint64_t Game::get_tick()
	{
		static LARGE_INTEGER frequency;
		static bool qpc = QueryPerformanceFrequency(&frequency);

		if (qpc)
		{
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			return (1000LL * now.QuadPart) / frequency.QuadPart; // Return in MS
		}
		else
			return GetTickCount();
	}

	Room *Game::create_room(bool activate)
	{
		_active_room = new Room(_window.get_graphics_controller(), BoundingBox{ Vector2{ 0, 0 }, 5000, 5000 });

		if (activate)
		{
			_active_room->activate_all();
		}

		return _active_room;
	}
}
