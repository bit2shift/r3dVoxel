#pragma once

/*
 * Enum<T> helpers
 */
#define ENUM_TYPE(x) using type = r3dVoxel::util::Enum<x>;
#define ENUM(x,...)  const type x(#x,##__VA_ARGS__);

namespace r3dVoxel
{
	namespace util
	{
		/*
		 * Enum<T> class for pseudo-reflection of enums
		 */
		template<typename T>
		class Enum final
		{
			static T m_counter;
			const char* m_name;
			const T m_value;

		public:
			Enum(const char* name, T init = m_counter) noexcept : m_name(name), m_value(init) {m_counter = T(init + 1);}
			const char* operator&() const noexcept {return m_name;}
			operator const T() const noexcept {return m_value;}
		};

		template<typename T>
		T Enum<T>::m_counter = 0;
	}
}
