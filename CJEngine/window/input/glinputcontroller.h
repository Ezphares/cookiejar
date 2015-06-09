#pragma once

#include <array>
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include <boost/bimap.hpp>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GLFW\glfw3.h>


#include <foundation\boundingbox.h>


struct GLFWwindow;

namespace cookiejar
{
	/*
	 * State
	 */
	typedef int JoystickEnumerator;

	struct JoystickState
	{
		std::vector<float> axes;
		std::vector<bool> buttons;
	};

	struct JoystickControl
	{
		JoystickState states[2];
		unsigned int current;
	};

	struct KeyboardState
	{
		std::array<bool, GLFW_KEY_LAST + 1> keys;
	};

	struct MouseState
	{
		std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> buttons;
		Point<float> position;
	};

	struct InputState
	{
		KeyboardState keyboard;
		MouseState mouse;
		std::map<JoystickEnumerator, JoystickControl> joysticks;
	};

	/*
	 * Mapping
	 */
	typedef int Command;

	typedef int KeyboardKey;
	typedef int MouseButton;
	typedef std::pair<KeyboardKey, KeyboardKey> KeyboardAxis;
	typedef std::pair<JoystickEnumerator, int> JoystickButton;
	typedef std::pair<JoystickEnumerator, int> JoystickAxis;

	struct InputMapping
	{
		boost::bimap<Command, KeyboardKey> keyboard_buttons;
		boost::bimap<Command, KeyboardAxis> keyboard_axes;
		boost::bimap<Command, JoystickButton> joystick_buttons;
		boost::bimap<Command, JoystickAxis> joystick_axes;
	};

	/*
	 * Events 
	 */
	typedef std::pair<KeyboardKey, bool> KeyEvent;
	typedef std::pair<JoystickButton, bool> JoystickEvent;
	typedef std::tuple<MouseButton, bool, Point<float> > MouseEvent;

	struct InputEvents
	{
		std::queue<KeyEvent> key_events;
		std::queue<JoystickEvent> joystick_events;
		std::queue<MouseEvent> mouse_events;
	};

	typedef std::pair<Command, bool> CommandEvent;
	struct TranslatedEvents
	{
		std::queue<CommandEvent> command_events;
		std::queue<MouseEvent> mouse_events;
	};

	class GLInputController
	{
	public:
		GLInputController();
		~GLInputController();

	public:
		void post_window_setup(GLFWwindow *window, Point<float> resolution_factor);
		void update();
		void clear_events();

		void register_keyboard_key(Command command, KeyboardKey key);
		void register_keyboard_axis(Command command, KeyboardKey negative, KeyboardKey positive);
		void register_joystick_button(Command command, JoystickButton button);
		void register_joystick_axis(Command command, JoystickAxis axis);

		float get_axis_state(Command axis);
		bool is_key_pressed(Command key);

		TranslatedEvents retrieve_events();

	private:
		void setup_joysticks();
		void translate_events();

	public:
		static InputState input_state;
		static InputEvents input_events;

	private:
		GLFWwindow *_window;
		InputMapping _mapping;
		Point<float> _resolution_factor;
		TranslatedEvents _translated_events;
	};
}
