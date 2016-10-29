#include "LargePool.Node.hpp"

#include "AllocUtils.hpp"
#include "LargePool.hpp"
#include "node_error.hpp"

#include <cstddef>

namespace r3dVoxel
{
	namespace memory
	{
		LargePool::Node::Node(std::size_t sz) : next(), pointer(AllocUtils::allocate(sz)), size(sz), length(sz)
		{
			if(!pointer)
				throw node_error("Cannot initialise node with %zu bytes.", sz);
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
			throw node_error("Cannot allocate node. LargePool's storage is full.");
		}

		void* LargePool::Node::operator new[](std::size_t size)
		{
			if(auto pointer = AllocUtils::allocate(size))
				return pointer;
			else
				throw node_error("Cannot allocate node array. We're probably out of memory.");
		}

		void LargePool::Node::operator delete[](void* pointer, std::size_t size) noexcept
		{
			AllocUtils::deallocate(pointer, size);
		}
	}
}
