#pragma once

/*
 * Enum<T> helpers
 */
#define ENUM_TYPE(x) using type = r3dVoxel::util::Enum<x>
#define ENUM(x)      constexpr type x{(__LINE__ - 1), #x}

namespace r3dVoxel::util
{
	/*
	 * Enum<T> struct for pseudo-reflection of enums
	 */
	template<typename T>
	struct Enum final
	{
		const T value;
		const char* name;

		constexpr operator const T() const noexcept {return value;}
		constexpr const char* operator&() const noexcept {return name;}
	};
}
