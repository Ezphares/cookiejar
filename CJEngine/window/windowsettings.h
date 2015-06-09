#pragma once

#include <stdint.h>
#include <string>

#include <foundation\vector.h>

namespace cookiejar
{
	struct WindowSettings
	{
		Point<uint32_t> size, resolution;
		bool fullscreen;
		std::string caption;
	};
}
