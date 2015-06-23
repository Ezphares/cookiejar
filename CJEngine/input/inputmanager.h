#pragma once

#include <foundation/activatable.h>

namespace cookiejar
{
	class InputManager :
		public Activatable < InputManager >
	{
	public:
		InputManager();
		~InputManager();
	};
}
