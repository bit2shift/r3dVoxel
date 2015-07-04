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

/*
 * std::put_time() IO manipulator missing on GCC 4.9 and earlier
 * Punch through ::r3dVoxel into the global namespace and put it on ::std
 */
#if __GNUC__ < 5
} //namespace r3dVoxel

namespace std
{
	template<typename char_t>
	struct __put_time_t
	{
		const tm* time;
		const char_t* format;
	};

	template<typename char_t>
	__put_time_t<char_t> put_time(const tm* time, const char_t* format)
	{
		return {time, format};
	}

	template<typename char_t, typename traits_t>
	basic_ostream<char_t, traits_t>&
	operator<<(basic_ostream<char_t, traits_t>& os, const __put_time_t<char_t>& pt)
	{
		__try
		{
			typename basic_ostream<char_t, traits_t>::sentry st(os);
			if(st)
			{
				typedef ostreambuf_iterator<char_t, traits_t> iter_t;
				typedef time_put<char_t, iter_t> tp_t;
				const tp_t& tp = use_facet<tp_t>(os.getloc());
				if(tp.put(iter_t(os), os, os.fill(), pt.time, pt.format, pt.format + traits_t::length(pt.format)).failed())
					os.setstate(ios_base::badbit);
			}
		}
		__catch(...)
		{
			os.setstate(ios_base::badbit);
		}
		return os;
	}
}

namespace r3dVoxel {
#endif

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
#define ENUM_TYPE(x)     typedef Enum<x> Enum;
#define ENUM_DECL(x,...) x(#x,##__VA_ARGS__)
#define ENUM(...)        const Enum ENUM_DECL(__VA_ARGS__);

/*
 * Logging level
 */
namespace ELoggingLevel
{
	ENUM_TYPE(std::uint8_t)
	ENUM(OFF)
	ENUM(SEVERE)
	ENUM(WARNING)
	ENUM(INFO)
	ENUM(DEBUG)
	ENUM(ALL)
}
