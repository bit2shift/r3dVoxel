#pragma once

#include "AllocUtils.hpp"

#include <cstddef>
#include <new>
#include <type_traits>

namespace r3dVoxel
{
	namespace memory
	{
		template<typename T>
		struct suballocator
		{
			using value_type = T;
			using propagate_on_container_move_assignment = std::true_type;
			using is_always_equal = std::true_type;

			suballocator() noexcept {}

			template<typename U>
			suballocator(const suballocator<U>&) noexcept {}

			T* allocate(std::size_t size)
			{
				if(auto pointer = AllocUtils::allocate(size))
					return static_cast<T*>(pointer);
				else
					throw std::bad_alloc();
			}

			void deallocate(T* pointer, std::size_t size)
			{
				AllocUtils::deallocate(pointer, size);
			}
		};

		template<typename A, typename B>
		bool operator==(const suballocator<A>&, const suballocator<B>&) noexcept
		{
			return true;
		}

		template<typename A, typename B>
		bool operator!=(const suballocator<A>&, const suballocator<B>&) noexcept
		{
			return false;
		}
	}
}
