#pragma once

#include "../../memory/suballocator.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace r3dVoxel
{
	namespace util
	{
		namespace bloom
		{
			template<template<typename...> class C, typename K, typename V>
			class container_adapter : public C<K, V>
			{
				static constexpr std::size_t BLOOM_THRESHOLD = 141;

				static constexpr std::array<std::size_t, 20> m_primes
				{
					 1381967,  2142557,  3120529,  4119233,  5544139,
					 6369859,  7411171,  8041087,  9733751, 10375241,
					11016611, 12307349, 13390771, 14478263, 15353293,
					16010747, 17329667, 18876743, 19321283, 20656201
				};

				using bloom_filter = std::pair<std::array<std::uint8_t, 4068>, std::uint8_t>;
				std::vector<bloom_filter, memory::suballocator<bloom_filter>> m_filters;

				std::size_t hash(K& key, std::size_t k)
				{
					std::size_t seed = m_primes[k];
					return seed ^ (std::hash<K>{}(key) + std::size_t(0x9E3779B97F4A7C16) + (seed << 6) + (seed >> 2));
				}

			public:
				container_adapter() noexcept {}

				//TODO add std::map methods
			};
		}
	}
}
