#include "AllocUtils.hpp"

#include <cstdint>
#include <cstdlib>
#include <new>

namespace r3dVoxel
{
	namespace memory
	{
		bool AllocUtils::valid(const void* pointer) noexcept
		{
			return (pointer && !(std::uintptr_t(pointer) & 15));
		}

		void** AllocUtils::clean(void* pointer, std::size_t size) noexcept
		{
			return reinterpret_cast<void**>(new(pointer) char[size]{});
		}

		void* AllocUtils::allocate(std::size_t size) noexcept
		{
			if(void* raw = std::malloc(size + 16))
			{
				void* pointer = reinterpret_cast<void*>((std::intptr_t(raw) + 16) & -16);
				clean(pointer, size)[-1] = raw;
				return pointer;
			}
			else
				return nullptr;
		}

		void AllocUtils::deallocate(void* pointer, std::size_t size) noexcept
		{
			if(valid(pointer))
				std::free(clean(pointer, size)[-1]);
		}
	}
}
