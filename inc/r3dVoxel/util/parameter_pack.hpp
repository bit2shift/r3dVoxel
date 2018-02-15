#pragma once

#include <cstddef>
#include <utility>

namespace r3dVoxel::util
{
	/*
	 * Parameter pack helper
	 */
	struct parameter_pack
	{
		template<typename F, typename T, typename... P>
		static constexpr void at(std::size_t index, F&& functor, T&& type, P&&... pack)
		{
			if(!index--)
				std::forward<F>(functor)(std::forward<T>(type));
			else
				at(index, std::forward<F>(functor), std::forward<P>(pack)...);
		}

		template<typename F>
		static constexpr void at(std::size_t, F&&){}

		template<typename F, typename T, typename... P>
		static constexpr void for_each(F&& functor, T&& type, P&&... pack)
		{
			std::forward<F>(functor)(std::forward<T>(type));
			for_each(std::forward<F>(functor), std::forward<P>(pack)...);
		}

		template<typename F>
		static constexpr void for_each(F&&){}

		template<typename T, typename... X, typename... Y>
		static constexpr T list_cast(Y&&... y)
		{
			return {X(std::forward<Y>(y))...};
		}
	};
}
