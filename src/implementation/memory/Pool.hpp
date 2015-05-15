#include <array>
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
		for(Root& root : m_hashtable)
		{
			Node* node = root.chain;
			while(node)
			{
				std::free(node->pointer);
				std::free(std::exchange(node, node->next));
			}
		}
	}

	void* create(std::size_t size)
	{
		char* pointer = talloc<char>(size + 15);
		Node* node = talloc<Node>(1);
		if(pointer && node)
		{
			Root& root = hashroot(pointer);
			root.size += size;

			node->size = size;
			node->pointer = pointer;
			node->next = std::exchange(root.chain, node);

			pointer += (15 - (std::uintptr_t(pointer - 1) & 15));
		}
		else
		{
			std::free(std::exchange(pointer, nullptr));
			std::free(std::exchange(node, nullptr));
		}
		return pointer;
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
					if(prev)
						prev->next = node->next;
					else
						root.chain = node->next;

					root.size -= node->size;
					std::free(node->pointer);
					std::free(node);
					break;
				}
				prev = std::exchange(node, node->next);
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
