#pragma once

/*
 * Enum<T> helpers
 */
#define ENUM_TYPE(x)     using type = r3dVoxel::util::Enum<x>;
#define ENUM_DECL(x,...) x(#x,##__VA_ARGS__)
#define ENUM(...)        const type ENUM_DECL(__VA_ARGS__);

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
			const char* m_name;
			const T m_value;
			static T m_counter;

		public:
			Enum(const char* name, T init = m_counter) noexcept : m_name(name), m_value(init) {m_counter = T(init + 1);}
			const char* name() const noexcept {return m_name;}
			const T value() const noexcept {return m_value;}
		};

		template<typename T>
		T Enum<T>::m_counter = 0;
	}
}
