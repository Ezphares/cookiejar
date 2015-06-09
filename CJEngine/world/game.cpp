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
		_initialized(false)
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
		auto *gfc = _window.get_graphics_controller();


		// DEBUG;
		Texture tx("spr.png");
		tx.bind();

		while (_window.is_running())
		{
			input->update();
			input->retrieve_events();
			input->clear_events();

			gfc->draw_start();
			gfc->draw_textured_rectangle({ 0, 0 }, { 32, 32 }, { 0, 0 }, { 1, 1 });
			gfc->draw_end();
		}
	}
}
