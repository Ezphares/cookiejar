#pragma once

namespace cookiejar
{
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
