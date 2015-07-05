#pragma once

/*
 * Type surrogate
 */
template<typename T> struct type_is {using type = T;};

/*
 * Copies "const" or "volatile" from type A to type B
 */
template<typename A, typename B> struct copy_cv                      : type_is<               B> {};
template<typename A, typename B> struct copy_cv<const          A, B> : type_is<const          B> {};
template<typename A, typename B> struct copy_cv<      volatile A, B> : type_is<      volatile B> {};
template<typename A, typename B> struct copy_cv<const volatile A, B> : type_is<const volatile B> {};

/*
 * Parameter pack helper
 */
struct parameter_pack
{
	template<typename F, typename T, typename... P>
	static void at(std::size_t index, F&& functor, T&& type, P&&... pack)
	{
		if(!index--)
			std::forward<F>(functor)(std::forward<T>(type));
		else
			at(index, std::forward<F>(functor), std::forward<P>(pack)...);
	}

	template<typename F>
	static void at(std::size_t, F&&){}

	template<typename F, typename T, typename... P>
	static void for_each(F&& functor, T&& type, P&&... pack)
	{
		std::forward<F>(functor)(std::forward<T>(type));
		for_each(std::forward<F>(functor), std::forward<P>(pack)...);
	}

	template<typename F>
	static void for_each(F&&){}
};

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
	Enum(const char* name, T init = m_counter) : m_name(name), m_value(init) {m_counter = T(init + 1);}

	const char* name() const {return m_name;}
	const T value() const {return m_value;}
};

template<typename T>
T Enum<T>::m_counter = 0;

/*
 * Enum<T> helpers
 */
#define ENUM_TYPE(x)     typedef r3dVoxel::Enum<x> Enum;
#define ENUM_DECL(x,...) x(#x,##__VA_ARGS__)
#define ENUM(...)        const Enum ENUM_DECL(__VA_ARGS__);
