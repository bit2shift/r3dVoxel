#include "LargePool.hpp"

#include "AllocUtils.hpp"

#include <r3dVoxel/bugfix/eclipse_cdt.hpp>
#include <cstdint>
#include <exception>
#include <functional>
#include <mutex>
#include <new>
#include <utility>

namespace r3dVoxel
{
	namespace memory
	{
		class ALIGN(16) Node
		{
			Node* m_next;
			std::size_t m_size;
			std::size_t m_length;
			std::size_t m_checksum;

			static std::size_t checksum(Node* node) noexcept
			{
				std::hash<std::size_t> hszt;
				std::size_t checksum = std::hash<Node*>()(node->m_next);
				checksum ^= (hszt(node->m_size) << 1);
				checksum ^= (hszt(node->m_length) << 3);
				return checksum;
			}

		public:
			Node(std::size_t size = 0) noexcept : m_next(nullptr), m_size(size), m_length(size), m_checksum(checksum(this)) {}

			void next(Node* next) noexcept
			{
				m_next = next;
				m_checksum = checksum(this);
			}

			void length(std::size_t length) noexcept
			{
				m_length = length;
				m_checksum = checksum(this);
			}

			Node* next()         noexcept {return m_next;}
			std::size_t size()   noexcept {return m_size;}
			std::size_t length() noexcept {return m_length;}
			bool valid()         noexcept {return (m_checksum == checksum(this));}

			static void* operator new(std::size_t size, std::size_t extra = 0)
			{
				if(void* pointer = AllocUtils::allocate(size + extra))
					return pointer;
				else
					throw std::bad_alloc();
			}

			static void* operator new[](std::size_t size)
			{
				if(void* pointer = AllocUtils::allocate(size))
					return pointer;
				else
					throw std::bad_alloc();
			}

			static void operator delete[](void* pointer, std::size_t size) noexcept
			{
				AllocUtils::deallocate(pointer, size);
			}
		};

		/* static */
		StaticLogger LargePool::logger("memory.log");

		/* static */
		void LargePool::deallocate(Node* branch) noexcept
		{
			while(branch)
			{
				if(branch->valid())
				{
					Node* tmp = std::exchange(branch, branch->next());
					AllocUtils::deallocate(tmp, tmp->size() + sizeof(Node));
				}
				else
				{
					logger("Corrupted node aka BUFFER-UNDERFLOW!!!");
					break;
				}
			}
		}

		/* static */
		template<typename P>
		void LargePool::insert(P&& predicate, Node* branch, Node* node) noexcept
		{
			while(branch)
			{
				if(!branch->valid())
				{
					logger("Corrupted node found during insertion.\n");
					std::terminate();
				}

				if(std::forward<P>(predicate)(branch))
				{
					node->next(branch->next());
					branch->next(node);
					break;
				}
				branch = branch->next();
			}
		}

		/* static */
		template<typename P>
		Node* LargePool::extract(P&& predicate, Node* branch) noexcept
		{
			Node* node = branch->next();
			while(node)
			{
				if(!node->valid())
				{
					logger("Corrupted node found during extraction.\n");
					std::terminate();
				}

				if(std::forward<P>(predicate)(node))
				{
					branch->next(node->next());
					node->next(nullptr);
					break;
				}
				branch = std::exchange(node, node->next());
			}
			return node;
		}

		Node* LargePool::access_table_branch(const void* pointer) noexcept
		{
			return (m_table + (std::uintptr_t(pointer) % m_size));
		}

		/*
		 * Preinitialize fields to ensure proper destruction upon exception
		 */
		LargePool::LargePool(std::size_t size) : m_stack(nullptr), m_table(nullptr), m_size(0), m_spinny()
		{
			m_stack = new Node();
			m_table = new Node[size];
			m_size = size;

			//TODO add me to Manager
		}

		LargePool::~LargePool()
		{
			//TODO remove me from Manager

			deallocate(m_stack);

			for(std::size_t i = 0; i < m_size; i++)
				deallocate(m_table[i].next());

			delete[] m_table;
		}

		void* LargePool::allocate(std::size_t size) noexcept
		{
			std::lock_guard<util::spin_lock> lock(m_spinny);

			/*
			 * Search stack for existing allocation.
			 * If found, subtract the node's size from the stack's length and update the node's length.
			 * Otherwise, create one.
			 * If creation fails, return nullptr.
			 */
			Node* node = extract([size](Node* n){return (n->size() >= size);}, m_stack);
			if(node)
			{
				m_stack->length(m_stack->length() - node->size());
				node->length(size);
			}
			else
			{
				try
				{
					node = new(size) Node(size);
				}
				catch(std::exception& e)
				{
					logger("Cannot allocate %zu bytes for new allocation. Reason: %s\n", size, e.what());
					return nullptr;
				}
			}

			/*
			 * Get table branch for (node + 1).
			 * Insert node into branch with all-true predicate.
			 * Add the node's size to branch's length.
			 * The allocated buffer is at (node + 1).
			 */
			Node* branch = access_table_branch(node + 1);
			insert([](Node* b){return true;}, branch, node);
			branch->length(branch->length() + node->size());
			return (node + 1);
		}

		void LargePool::deallocate(void* pointer) noexcept
		{
			std::lock_guard<util::spin_lock> lock(m_spinny);

			/*
			 * Get table branch for pointer.
			 * Extract node from branch where pointer is (n + 1).
			 * Subtract the node's size from the branch's length.
			 * Insert node into stack with all-true predicate.
			 * Add the node's size to the stack's length.
			 */
			Node* branch = access_table_branch(pointer);
			if(Node* node = extract([pointer](Node* n){return (pointer == (n + 1));}, branch))
			{
				branch->length(branch->length() - node->size());
				insert([](Node* b){return true;}, m_stack, node);
				m_stack->length(m_stack->length() + node->size());
			}
		}

		std::size_t LargePool::total() noexcept
		{
			std::size_t total = m_stack->length();
			for(std::size_t i = 0; i < m_size; i++)
				total += m_table[i].length();
			return total;
		}

		std::size_t LargePool::query(const void* pointer) noexcept
		{
			std::lock_guard<util::spin_lock> lock(m_spinny);

			Node* node = access_table_branch(pointer)->next();
			while(node)
			{
				if(pointer == (node + 1))
					return node->length();
				node = node->next();
			}
			return 0;
		}
	}
}
