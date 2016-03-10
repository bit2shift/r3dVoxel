#include "AllocUtils.hpp"

#include <cstdint>
#include <cstdlib>
#include <new>

static void* alloc(std::size_t size) noexcept
{
	if(void* raw = std::malloc(size + 16))
	{
		void* pointer = reinterpret_cast<void*>((std::intptr_t(raw) + 16) & -16);
		reinterpret_cast<void**>(pointer)[-1] = raw;
		return pointer;
	}
	else
		return nullptr;
}

static void dealloc(void* pointer) noexcept
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
			if(void* pointer = (alignof(std::max_align_t) >= 16) ? std::malloc(size) : alloc(size))
			{
				clean(pointer, size);
				total += size;
				return pointer;
			}
			else
				return nullptr;
		}

		void AllocUtils::deallocate(void* pointer, std::size_t size) noexcept
		{
			if(valid(pointer))
			{
				total -= size;
				clean(pointer, size);

				if(alignof(std::max_align_t) >= 16)
					std::free(pointer);
				else
					dealloc(pointer);
			}
		}
	}
}
