#include <array>
#include <cstdlib>
#include <utility>

/*
 * std::calloc() type wrapper
 */
template<typename T>
T* talloc(std::size_t count)
{
	return static_cast<T*>(std::calloc(count, sizeof(T)));
}

/*
 * Allocation pool
 */
class Pool
{
	struct Node
	{
		std::size_t size;
		void* pointer;
		Node* next;
	};

	struct Root
	{
		std::size_t size;
		Node* chain;
	};

	// std::array -> internal array -> Root -> zero-initialize
	std::array<Root, 256> m_hashtable = {{{0}}};

	// suits both 32-bit and 64-bit pointers
	Root& hashroot(const void* pointer)
	{
		return m_hashtable[std::uintptr_t(pointer) >> 24 & 0xFF];
	}

public:
	~Pool()
	{
		//XXX log still-allocated memory?
		for(Root& root : m_hashtable)
		{
			Node* node = root.chain;
			while(node)
			{
				void* pointer = node->pointer;
				std::free(std::exchange(node, node->next));
				std::free(pointer);
			}
			root = {0};
		}
	}

	void* create(std::size_t size)
	{
		Node* node = talloc<Node>(1);
		char* pointer = talloc<char>(size + 15);
		if(node && pointer)
		{
			Root& root = hashroot(pointer);
			root.size += size;

			node->size = size;
			node->pointer = pointer;
			node->next = root.chain;
			root.chain = node;

			pointer += (15 - (std::uintptr_t(pointer - 1) & 15));
			return pointer;
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
		if(pointer)
		{
			Root& root = hashroot(pointer);
			Node* node = root.chain;
			Node* prev = nullptr;
			while(node)
			{
				if((std::uintptr_t(pointer) - std::uintptr_t(node->pointer)) < 16)
				{
					root.size -= node->size;
					pointer = node->pointer;

					if(prev)
						prev->next = node->next;
					else
						root.chain = node->next;

					std::free(node);
					std::free(pointer);
					break;
				}
				prev = node;
				node = node->next;
			}
		}
	}

	std::size_t usage()
	{
		std::size_t total = 0;
		for(Root& root : m_hashtable)
			total += root.size;
		return total;
	}
};
