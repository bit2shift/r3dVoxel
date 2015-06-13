/*
 * Useful "pretty" things in here.
 */

/*
 * Defines a monitor's video mode. Valid if refresh is not zero.
 * Example:
 *   SVideoMode vm = {800, 600, 8, 8, 8, 59};
 */
struct SVideoMode
{
	std::int16_t width;   //screen width in pixels
	std::int16_t height;  //screen height in pixels
	std::int8_t red;      //red channel bit depth
	std::int8_t green;    //green channel bit depth
	std::int8_t blue;     //blue channel bit depth
	std::int8_t refresh;  //how fast the screen is refreshed
};

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
