#include "AlignedAlloc.hpp"

#include <cstdint>
#include <cstdlib>

namespace r3dVoxel
{
	namespace memory
	{
		inline void** clean(void* pointer, std::size_t size) noexcept
		{
			return reinterpret_cast<void**>(new(pointer) char[size]{});
		}

		void* AlignedAlloc::allocate(std::size_t size) noexcept
		{
			void* raw = std::malloc(size + 16);
			if(!raw)
				return nullptr;

			void* pointer = reinterpret_cast<void*>((std::uintptr_t(raw) + 16) & ~15ULL);
			clean(pointer, size)[-1] = raw;
			return pointer;
		}

		void AlignedAlloc::deallocate(void* pointer, std::size_t size) noexcept
		{
			if(pointer)
				std::free(clean(pointer, size)[-1]);
		}
	}
}
