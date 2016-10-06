#include "LargePool.Node.hpp"

#include "AllocUtils.hpp"

#include <cstddef>
#include <new>

namespace r3dVoxel
{
	namespace memory
	{
		LargePool::Node::Node(std::size_t sz) : next(), pointer(AllocUtils::allocate(sz)), size(sz), length(sz)
		{
			if(!pointer)
			{
				MM_LOGGER("[RUNNING LOW ON MEMORY] Cannot allocate node with %zu bytes.\n", sz);
				throw std::bad_alloc();
			}
		}

		LargePool::Node::~Node()
		{
			AllocUtils::deallocate(pointer, size);
			(*this) = {};
		}

		void* LargePool::Node::operator new(std::size_t, LargePool* pool)
		{
			for(std::size_t i = 0; i < NODE_COUNT; i++)
			{
				auto node = &pool->m_storage[i];
				if(!node->pointer)
					return node;
			}
			throw std::bad_alloc();
		}

		void* LargePool::Node::operator new[](std::size_t size)
		{
			if(auto pointer = AllocUtils::allocate(size))
				return pointer;
			else
				throw std::bad_alloc();
		}

		void LargePool::Node::operator delete[](void* pointer, std::size_t size) noexcept
		{
			AllocUtils::deallocate(pointer, size);
		}
	}
}
