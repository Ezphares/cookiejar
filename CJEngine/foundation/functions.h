#pragma once

#include <memory>

#define CJ_BEHAVIOUR_SCRIPT(name) void name(const Entity &self, Component *component, void *arg)

namespace cookiejar
{
	struct Entity;

	typedef void(*BehaviourScript)(const Entity &, Component *, void *);
	
	inline void nop_delete(void *){};
	inline std::shared_ptr<void> no_arg()
	{
		return std::shared_ptr<void>(NULL, nop_delete);
	}

	inline CJ_BEHAVIOUR_SCRIPT(nop)
	{
	}
}
