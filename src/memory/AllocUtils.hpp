#pragma once

#include <cstddef>

namespace r3dVoxel
{
	namespace memory
	{
		class AllocUtils
		{
		public:
			static bool valid(const void* pointer) noexcept;
			static void** clean(void* pointer, std::size_t size) noexcept;

			static void* allocate(std::size_t size) noexcept;
			static void deallocate(void* pointer, std::size_t size) noexcept;
		};
	}
}
