#pragma once

#ifndef NULL
#define NULL 0
#endif

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
		inline Activatable(){}
		virtual inline ~Activatable(){}

		void activate()
		{
			Activatable<T>::ACTIVE = dynamic_cast<T *>(this);
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
