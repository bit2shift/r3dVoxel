#include "AllocUtils.hpp"

#include <cstdint>
#include <cstdlib>

namespace r3dVoxel
{
	namespace memory
	{
		bool AllocUtils::valid(const void* pointer) noexcept
		{
			return (pointer && !(std::uintptr_t(pointer) & 15ULL));
		}

		void** AllocUtils::clean(void* pointer, std::size_t size) noexcept
		{
			return reinterpret_cast<void**>(new(pointer) char[size]{});
		}

		void* AllocUtils::allocate(std::size_t size) noexcept
		{
			void* raw = std::malloc(size + 16);
			if(!raw)
				return nullptr;

			void* pointer = reinterpret_cast<void*>((std::uintptr_t(raw) + 16) & ~15ULL);
			clean(pointer, size)[-1] = raw;
			return pointer;
		}

		void AllocUtils::deallocate(void* pointer, std::size_t size) noexcept
		{
			if(valid(pointer))
				std::free(clean(pointer, size)[-1]);
		}
	}
}
