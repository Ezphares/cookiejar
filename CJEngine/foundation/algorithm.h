#pragma once

namespace cookiejar
{
	template <typename T>
	inline T sign(T source)
	{
		return source < 0 ? static_cast<T>(-1) : static_cast<T>(1);
	}
}
