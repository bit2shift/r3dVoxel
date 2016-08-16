#pragma once

#include "StaticLogger.hpp"

#include <r3dVoxel/util/spin_lock.hpp>
#include <cstddef>
#include <memory>

namespace r3dVoxel
{
	namespace memory
	{
		class LargePool
		{
			struct Node;

			static constexpr std::size_t TABLE_SIZE{1 << 8};
			static constexpr std::size_t NODE_COUNT{1 << 16};
			static constexpr StaticLogger MM_LOGGER{"memory.log"};

			std::unique_ptr<Node[]> m_storage;
			std::unique_ptr<Node[]> m_table;
			Node* m_stack;

			util::spin_lock m_spinny;

			Node* acquire() noexcept;
			void release(Node* node) noexcept;
			Node* branch(const void* pointer) noexcept;

		public:
			LargePool();
			~LargePool();

			void* allocate(std::size_t size) noexcept;
			void deallocate(void* pointer) noexcept;
			std::size_t total() noexcept;
			std::size_t query(const void* pointer) noexcept;
		};
	}
}
