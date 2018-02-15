#pragma once

/*
 * Enumeration helpers
 */
#define ENUM_TYPE(name,type) struct name final : r3dVoxel::util::Enum<name, type, __COUNTER__>
#define ENUM_VALUE(name)     static constexpr Enum name{__COUNTER__, #name}

namespace r3dVoxel::util
{
	/*
	 * Enumeration structure for pseudo-reflection of enumerations
	 */
	template<typename T, typename V, V initial>
	struct Enum
	{
		constexpr Enum(const V value, const char* name) noexcept : m_value{V(~initial + value)}, m_name{name} {}

		constexpr             operator const T&() const noexcept {return static_cast<const T&>(*this);}
		constexpr             operator const V()  const noexcept {return m_value;}
		constexpr const char* operator&()         const noexcept {return m_name;}

	private:
		const V m_value;
		const char* m_name;
	};
}
