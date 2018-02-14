#include "AllocUtils.hpp"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>

static void* alloc(std::size_t size) noexcept
{
	if constexpr(alignof(std::max_align_t) >= 16)
		return std::malloc(size);
	else if(auto raw = std::malloc(size + 16))
	{
		auto pointer = reinterpret_cast<void*>((std::intptr_t(raw) + 16) & -16);
		reinterpret_cast<void**>(pointer)[-1] = raw;
		return pointer;
	}
	else
		return nullptr;
}

static void dealloc(void* pointer) noexcept
{
	if constexpr(alignof(std::max_align_t) >= 16)
		std::free(pointer);
	else
		std::free(reinterpret_cast<void**>(pointer)[-1]);
}

namespace r3dVoxel::memory
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
		if(auto pointer = alloc(size))
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
			dealloc(clean(pointer, size));
		}
	}
}
