#pragma once

namespace r3dVoxel::util
{
	namespace detail
	{
		template<typename A, typename B> struct copy_cv                      {using type = B               ;};
		template<typename A, typename B> struct copy_cv<A const         , B> {using type = B const         ;};
		template<typename A, typename B> struct copy_cv<A       volatile, B> {using type = B       volatile;};
		template<typename A, typename B> struct copy_cv<A const volatile, B> {using type = B const volatile;};
	}

	/*
	 * Copies "const" or "volatile" from type A to type B
	 */
	template<typename A, typename B>
	using copy_cv = typename detail::copy_cv<A, B>::type;
}
