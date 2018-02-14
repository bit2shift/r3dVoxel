#pragma once

#include <atomic>
#include <cstddef>

namespace r3dVoxel::memory
{
	class AllocUtils
	{
	public:
		static std::atomic_size_t total;

		static bool valid(const void* pointer) noexcept;
		static void* clean(void* pointer, std::size_t size) noexcept;

		static void* allocate(std::size_t size) noexcept;
		static void deallocate(void* pointer, std::size_t size) noexcept;
	};
}
