#pragma once

#include "StaticLogger.hpp"

#include <r3dVoxel/util/spin_lock.hpp>
#include <cstddef>

namespace r3dVoxel
{
	namespace memory
	{
		class Node;

		class LargePool
		{
			Node* m_stack;
			Node* m_table;
			std::size_t m_size;

			util::spin_lock m_spinny;

			static StaticLogger logger;
			static void deallocate(Node* branch) noexcept;

			template<typename P>
			static void insert(P&& predicate, Node* branch, Node* node) noexcept;

			template<typename P>
			static Node* extract(P&& predicate, Node* branch) noexcept;

			Node* access_table_branch(const void* pointer) noexcept;

		public:
			LargePool(std::size_t size);
			~LargePool();

			void* allocate(std::size_t size) noexcept;
			void deallocate(void* pointer) noexcept;
			std::size_t total() noexcept;
			std::size_t query(const void* pointer) noexcept;
		};
	}
}
