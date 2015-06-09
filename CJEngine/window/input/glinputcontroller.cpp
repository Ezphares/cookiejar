#include "glinputcontroller.h"

namespace cookiejar
{
	InputState GLInputController::input_state = {};
	InputEvents GLInputController::input_events = {};

	/* Local callbacks */
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action != GLFW_REPEAT && key >= 0 )
		{
			GLInputController::input_state.keyboard.keys[key] = (action == GLFW_PRESS);
			GLInputController::input_events.key_events.push(std::make_pair(key, (action == GLFW_PRESS) ));
		}
	}

	void mouse_callback(GLFWwindow *window, int button, int action, int mods)
	{
		if (button >= 0)
		{
			GLInputController::input_state.mouse.buttons[button] = (action == GLFW_PRESS);
			GLInputController::input_events.mouse_events.push( std::make_tuple( button, (action == GLFW_PRESS), GLInputController::input_state.mouse.position ) );
		}
	}

	void mouse_positon_callback(GLFWwindow *window, double x, double y)
	{
		GLInputController::input_state.mouse.position = { static_cast<float>(x), static_cast<float>(y) };
	}

	GLInputController::GLInputController() : _mapping()
	{
	}


	GLInputController::~GLInputController()
	{
	}

	void GLInputController::post_window_setup(GLFWwindow *window, Point<float> resolution_factor)
	{
		_window = window;
		_resolution_factor = resolution_factor;
		
		setup_joysticks();

		clear_events();

		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_callback);
		glfwSetCursorPosCallback(window, mouse_positon_callback);
	}

	void GLInputController::update()
	{
		glfwPollEvents();

		// Update joysticks
		for (auto it = GLInputController::input_state.joysticks.begin();
			it != GLInputController::input_state.joysticks.end();
			++it)
		{
			JoystickControl control = it->second;

			auto prev = control.states[control.current];
			control.current = (0 - control.current) + 1;
			auto curr = control.states[control.current];

			int count = 0;
			const float *axes = glfwGetJoystickAxes(it->first, &count);
			curr.axes = std::vector<float>(axes, axes + count);
			const unsigned char *buttons = glfwGetJoystickButtons(it->first, &count);
			bool *bpress = new bool[count];
			for (int i = 0; i < count; ++i)
			{
				bpress[i] = (buttons[i] == GLFW_PRESS );

				if (bpress[i] && !prev.buttons[i])
				{
					//GLInputController::input_events.joystick_events.push() PRESS EVENT
				}
				else if (!bpress[i] && prev.buttons[i])
				{
					// RELEASE EVENT
				}
			}
			curr.buttons = std::vector<bool>(bpress, bpress + count);
		}

		translate_events();
	}

	void GLInputController::clear_events()
	{
		// Raw events
		std::queue<KeyEvent> key_empty;
		std::queue<JoystickEvent> joystick_empty;
		std::queue<MouseEvent> mouse_empty;

		std::swap(key_empty, GLInputController::input_events.key_events);
		std::swap(joystick_empty, GLInputController::input_events.joystick_events);
		std::swap(mouse_empty, GLInputController::input_events.mouse_events);

		// Translated events
		std::queue<MouseEvent> translated_mouse_empty;
		std::queue<CommandEvent> translated_command_empty;

		std::swap(translated_mouse_empty, _translated_events.mouse_events);
		std::swap(translated_command_empty, _translated_events.command_events);

	}

	float GLInputController::get_axis_state(Command axis)
	{
		// Keyb = (Command, KeyboardAxis)
		// KeyboardAxis = (KeyboadKey(-)  ,  KeyboardKey(+))
		auto keyb = _mapping.keyboard_axes.left.find(axis);
		if (keyb != _mapping.keyboard_axes.left.end())
		{
			// Int used for calulations (floating point precision might not land us back at 0)
			int value = 0;
			if (GLInputController::input_state.keyboard.keys[keyb->second.first])
			{
				value -= 1;
			}
			if (GLInputController::input_state.keyboard.keys[keyb->second.second])
			{
				value += 1;
			}

			return (float)value;
		}

		// Joy = (Command, JoystickAxis)
		// JoystickAxis = (JoystickIndex  ,  AxisIndex)
		auto joy = _mapping.joystick_axes.left.find(axis);
		if (joy != _mapping.joystick_axes.left.end())
		{
			int count = 0;
			const float *axes = glfwGetJoystickAxes(joy->second.first, &count);
			int index = joy->second.second;
			if (index >= count)
			{
				throw 23; //TODO: InputException
			}

			return axes[index];
		}

		// Unmapped axis
		throw 24; //TODO: InputException
	}

	bool GLInputController::is_key_pressed(Command key)
	{
		// Key = (Command, KeyboardKey)
		auto keyb = _mapping.keyboard_buttons.left.find(key);
		if (keyb != _mapping.keyboard_buttons.left.end())
		{
			return GLInputController::input_state.keyboard.keys[keyb->second];
		}
		// Joy = (Command, JoystickButton)
		// JoystickButton = (JoystickIndex  ,  ButtonIndex)
		auto joy = _mapping.joystick_buttons.left.find(key);
		if (joy != _mapping.joystick_buttons.left.end())
		{
			int count = 0;
			const unsigned char *buttons = glfwGetJoystickButtons(joy->second.first, &count);
			int index = joy->second.second;
			if (index >= count)
			{
				throw 23; //TODO: InputException
			}

			return (buttons[index] == GLFW_PRESS);
		}

		// Unmapped key
		throw 24; //TODO: InputException
	}

	void GLInputController::register_keyboard_key(Command command, KeyboardKey key)
	{
		// TODO: Unbind key from keyboard

		typedef boost::bimap<Command, KeyboardKey>::value_type kbmap;
		_mapping.keyboard_buttons.insert( kbmap(command, key) );
	}

	void GLInputController::register_keyboard_axis(Command command, KeyboardKey neg, KeyboardKey pos)
	{
		// TODO: Unbind keys from keyboard

		typedef boost::bimap<Command, KeyboardAxis>::value_type kbamap;
		_mapping.keyboard_axes.insert( kbamap(command, std::make_pair(neg, pos)) );
	}

	void GLInputController::register_joystick_button(Command command, JoystickButton button)
	{
		// TODO: Unbind button from joystick

		typedef boost::bimap<Command, JoystickAxis>::value_type joymap;
		_mapping.joystick_buttons.insert(joymap(command, button));
	}


	void GLInputController::register_joystick_axis(Command command, JoystickAxis axis)
	{
		// TODO: Unbind axis from joystick

		typedef boost::bimap<Command, JoystickAxis>::value_type joyamap;
		_mapping.joystick_axes.insert(joyamap(command, axis));
	}

	TranslatedEvents GLInputController::retrieve_events()
	{
		return _translated_events;
	}

	void GLInputController::setup_joysticks()
	{
		GLInputController::input_state.joysticks.clear();

		// Search for connected joysticks
		for (JoystickEnumerator i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; ++i)
		{
			if (glfwJoystickPresent(i))
			{
				JoystickState state = {};

				int count;
				glfwGetJoystickAxes(i, &count);
				state.axes.resize(count, 0.0f);
				glfwGetJoystickButtons(i, &count);
				state.buttons.resize(count, false);

				JoystickControl control = { { state, state }, 0};

				GLInputController::input_state.joysticks[i] = control;
			}
		}
	}

	void GLInputController::translate_events()
	{
		// Mouse
		auto &mouse = GLInputController::input_events.mouse_events;
		while (!mouse.empty())
		{
			auto &event = mouse.front();
			Point<float> internal_position = std::get<2>(event) * _resolution_factor;
			_translated_events.mouse_events.push(std::make_tuple(std::get<0>(event), std::get<1>(event), internal_position));
			mouse.pop();
		}

		/*
		 * Merge joystick events and keyboard events into bound "command events"
		 */

		// Keyboard events
		auto &keyboard = GLInputController::input_events.key_events;
		while (!keyboard.empty())
		{
			auto &event = keyboard.front();
			// map = (key -> command)
			auto &map = _mapping.keyboard_buttons.right;

			auto binding = map.find(event.first);
			if (binding != map.end())
			{
				_translated_events.command_events.push(std::make_pair(binding->second, event.second));
			}

			keyboard.pop();
		}

		// Joystick events
		auto &joystick = GLInputController::input_events.joystick_events;
		while (!joystick.empty())
		{
			auto &event = joystick.front();
			// map = (button -> command)
			auto &map = _mapping.joystick_buttons.right;

			auto binding = map.find(event.first);
			if (binding != map.end())
			{
				_translated_events.command_events.push(std::make_pair(binding->second, event.second));
			}

			joystick.pop();
		}
	}
}
