#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <forward_list>
#include <functional>
#include <memory>
#include <utility>

namespace r3dVoxel
{
	namespace util
	{
		template<typename C>
		class bloom_filter : public C
		{
			using key_type = typename C::key_type;

			template<typename T>
			using allocator_type = typename std::allocator_traits<typename C::allocator_type>::template rebind_alloc<T>;

			using filter_type = std::pair<std::array<std::uint8_t, 4068>, std::uint8_t>;

			static constexpr std::size_t THRESHOLD = 141;
			static constexpr std::array<std::size_t, 20> PRIMES
			{
				 1381967,  2142557,  3120529,  4119233,  5544139,
				 6369859,  7411171,  8041087,  9733751, 10375241,
				11016611, 12307349, 13390771, 14478263, 15353293,
				16010747, 17329667, 18876743, 19321283, 20656201
			};

			std::forward_list<filter_type, allocator_type<filter_type>> m_filters{1};

			static std::size_t hash(const key_type& key, std::size_t prime) noexcept
			{
				return (prime ^ (std::hash<key_type>{}(key) + std::size_t(0x9E3779B97F4A7C16) + (prime << 6) + (prime >> 2))) % std::tuple_size<filter_type::first_type>::value;
			}

			/*
			 * Evaluates a predicate over a group of buckets selected by the hash values of the key.
			 * If the predicate is true, this function will return false to signal an incomplete iteration.
			 * Otherwise it will return true on a complete iteration over all buckets.
			 * Note: The predicate can be impure, if modifying the bucket values.
			 */
			static bool bucket_do(filter_type& filter, const key_type& key, bool(*predicate)(std::uint8_t&)) noexcept
			{
				for(std::size_t prime : PRIMES)
				{
					if(predicate(filter.first[hash(key, prime)]))
						return false;
				}
				return true;
			}

		public:
			bool test(const key_type& key) noexcept
			{
				for(filter_type& filter : m_filters)
				{
					if(bucket_do(filter, key, [](std::uint8_t& bucket){return !bucket;}))
						return true;
				}
				return false;
			}

			void add(const key_type& key) noexcept
			{
				filter_type& filter = (m_filters.front().second == THRESHOLD) ? m_filters.emplace_front() : m_filters.front();
				bucket_do(filter, key, [](std::uint8_t& bucket){return (++bucket, false);});
				++filter.second;
			}

			bool remove(const key_type& key) noexcept
			{
				for(filter_type& filter : m_filters)
				{
					if(bucket_do(filter, key, [](std::uint8_t& bucket){return !bucket;}))
					{
						--filter.second;
						bucket_do(filter, key, [](std::uint8_t& bucket){return (--bucket, false);});
						m_filters.remove_if([](const filter_type& filter){return !filter.second;});
						return true;
					}
				}
				return false;
			}

		public:
			bloom_filter() noexcept {}

			//TODO add std::map methods
		};
	}
}
