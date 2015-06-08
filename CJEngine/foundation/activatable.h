#pragma once

namespace cookiejar
{
	/*
	 * Inherit this to create a pseudo-singleton class.
	 * Multiple instances of it can exist, but only one is active at a time.
	 */
	template <typename T>
	class Activatable
	{
	public:
		void activate()
		{
			Activatable<T>::ACTIVE = *this;
		}

		static T* active()
		{
			return Activatable<T>::ACTIVE;
		}

	private:
		static T* ACTIVE;
	};

	template<typename T>
	T* Activatable<T>::ACTIVE = NULL;
}
