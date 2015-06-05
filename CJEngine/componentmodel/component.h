#pragma once

#include <cstdint>

namespace cookiejar
{
	typedef std::uint16_t ComponentType;

	class Component
	{
	public:
		inline Component() {};
		virtual inline ~Component()
		{}
	};
}
