#pragma once

namespace r3dVoxel
{
	namespace util
	{
		/*
		 * Type surrogate
		 */
		template<typename T> struct type_is {using type = T;};

		/*
		 * Copies "const" or "volatile" from type A to type B
		 */
		template<typename A, typename B> struct copy_cv                      : type_is<B               > {};
		template<typename A, typename B> struct copy_cv<A const         , B> : type_is<B const         > {};
		template<typename A, typename B> struct copy_cv<A       volatile, B> : type_is<B       volatile> {};
		template<typename A, typename B> struct copy_cv<A const volatile, B> : type_is<B const volatile> {};
	}
}
