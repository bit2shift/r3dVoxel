#pragma once

#include <ctime>
#include <ios>
#include <locale>

/*
 * std::put_time() IO manipulator missing on GCC 4.9 and earlier
 */
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
