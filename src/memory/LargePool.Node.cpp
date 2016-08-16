#include "LargePool.Node.hpp"

#include "AllocUtils.hpp"

#include <cstddef>
#include <cstdio>
#include <new>

namespace r3dVoxel
{
	namespace memory
	{
		class bad_node_alloc : public std::bad_alloc
		{
			static thread_local char BUFFER[64];

		public:
			bad_node_alloc(std::size_t size) noexcept
			{
				std::snprintf(BUFFER, sizeof(BUFFER), "Cannot allocate node with %zu bytes.", size);
			}

			const char* what() const noexcept
			{
				return BUFFER;
			}
		};

		thread_local char bad_node_alloc::BUFFER[];

		LargePool::Node::Node(std::size_t sz) : pointer(AllocUtils::allocate(sz)), size(sz), length(sz)
		{
			if(!pointer)
				throw bad_node_alloc(sz);
		}

		LargePool::Node::~Node()
		{
			AllocUtils::deallocate(pointer, size);
			(*this) = {};
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
