#pragma once

#include "LargePool.hpp"

#include <cstddef>

namespace r3dVoxel
{
	namespace memory
	{
		struct LargePool::Node
		{
			alignas(8) Node* next{};
			alignas(8) void* pointer{};
			alignas(8) std::size_t size{};
			alignas(8) std::size_t length{};

			Node() noexcept {}
			Node(std::size_t sz);
			~Node();

			static void* operator new(std::size_t) = delete;
			static void operator delete(void*) noexcept = delete;

			static void* operator new[](std::size_t size);
			static void operator delete[](void* pointer, std::size_t size) noexcept;
		};
	}
}
