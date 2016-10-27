#include "AllocUtils.hpp"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>

template<bool = false>
void* alloc(std::size_t size) noexcept
{
	return std::malloc(size);
}

template<>
void* alloc<true>(std::size_t size) noexcept
{
	if(auto raw = std::malloc(size + 16))
	{
		auto pointer = reinterpret_cast<void*>((std::intptr_t(raw) + 16) & -16);
		reinterpret_cast<void**>(pointer)[-1] = raw;
		return pointer;
	}
	else
		return nullptr;
}

template<bool = false>
void dealloc(void* pointer) noexcept
{
	std::free(pointer);
}

template<>
void dealloc<true>(void* pointer) noexcept
{
	std::free(reinterpret_cast<void**>(pointer)[-1]);
}

namespace r3dVoxel
{
	namespace memory
	{
		std::atomic_size_t AllocUtils::total{0};

		bool AllocUtils::valid(const void* pointer) noexcept
		{
			return (pointer && !(std::uintptr_t(pointer) & 15));
		}

		void* AllocUtils::clean(void* pointer, std::size_t size) noexcept
		{
			return new(pointer) char[size]{};
		}

		void* AllocUtils::allocate(std::size_t size) noexcept
		{
			if(auto pointer = alloc<alignof(std::max_align_t) < 16>(size))
			{
				total += size;
				return clean(pointer, size);
			}
			else
				return nullptr;
		}

		void AllocUtils::deallocate(void* pointer, std::size_t size) noexcept
		{
			if(valid(pointer))
			{
				total -= size;
				dealloc<alignof(std::max_align_t) < 16>(clean(pointer, size));
			}
		}
	}
}
