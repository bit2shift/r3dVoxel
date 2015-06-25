#include <array>
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <utility>

/*
 * Allocation pool
 */
class Pool
{
	struct Lock
	{
		static std::atomic_flag& flag()
		{
			static std::atomic_flag instance = ATOMIC_FLAG_INIT;
			return instance;
		}

		Lock() { while(flag().test_and_set(std::memory_order_acquire)); }
		~Lock(){       flag().clear(std::memory_order_release);         }
	};

	struct Node
	{
		Node* next;
		std::size_t size;
		void* pointer;
	};

	struct Root
	{
		Node* chain;
		std::size_t size;
	};

	// std::array -> internal array -> Root -> zero-initialize
	std::array<Root, 256> m_hashtable = {{{0}}};

	// suits both 32-bit and 64-bit pointers
	Root* hashroot(const void* pointer)
	{
		return &m_hashtable[std::uintptr_t(pointer) % m_hashtable.size()];
	}

	template<typename T>
	T* talloc(std::size_t count)
	{
		return static_cast<T*>(std::calloc(count, sizeof(T)));
	}

public:
	~Pool()
	{
		//XXX log still-allocated memory?
		for(Root root : m_hashtable)
		{
			Node* node = root.chain;
			while(node)
			{
				void* pointer = node->pointer;
				std::free(std::exchange(node, node->next));
				std::free(pointer);
			}
		}
	}

	void* create(std::size_t size)
	{
		Lock lock;
		Node* node = talloc<Node>(1);
		char* pointer = talloc<char>(size + 15);
		if(node && pointer)
		{
			Root* root = hashroot(pointer);
			*node = {root->chain, size, pointer};
			root->chain = node;
			root->size += size;
			return pointer + (15 - (std::uintptr_t(pointer - 1) & 15));
		}
		else
		{
			std::free(node);
			std::free(pointer);
			return nullptr;
		}
	}

	void destroy(void* pointer)
	{
		Lock lock;
		Root* root = hashroot(pointer);
		Node* prev = reinterpret_cast<Node*>(root);
		Node* node = root->chain;
		while(node)
		{
			if((std::uintptr_t(pointer) - std::uintptr_t(node->pointer)) < 16)
			{
				prev->next = node->next;
				root->size -= node->size;
				pointer = node->pointer;
				std::free(node);
				std::free(pointer);
				break;
			}
			prev = std::exchange(node, node->next);
		}
	}

	std::size_t usage()
	{
		std::size_t total = 0;
		for(Root root : m_hashtable)
			total += root.size;
		return total;
	}
};
