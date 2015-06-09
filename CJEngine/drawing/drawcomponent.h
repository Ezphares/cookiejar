#pragma once

#include "drawinterface.h"

#include <componentmodel\component.h>
#include <foundation\functions.h>

namespace cookiejar
{
	class Draw : public Component
	{
	public:
		Draw(BehaviourScript script = NULL) :
			script(script)
		{}

		BehaviourScript script;
	};
}
