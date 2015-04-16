/*
 * ~~~~Abstract~~~~
 * INTERNAL
 * This infrastructure delegates all memory allocations.
 * Allocated memory is 16-byte aligned.
 */

//XXX the functions should be atomic

/*
 * Memory pool handler
 */
class MemPool
{
	unsigned m_table_size;
	void** m_table_pointer;

	/*
	 * Memory metadata
	 * Allocation size = 15 (pad) + 5 (meta) + N (length)
	 * MM_meta::offset <- char(20 - (unsigned(pointer + 4) & 15))
	 * MM_meta::size <- N
	 * Access to MM_meta::size MIGHT LOOK unaligned, but it will be 4 bytes behind the pointer
	 */
	struct MemMeta
	{
		char offset;    //range: [5, 20]
		unsigned size;  //block size
	}__attribute((gcc_struct, packed));

	/* Adds pointer to pool, returns false if pool full */
	bool addPointer(void* pointer)
	{
		for(unsigned i = 0; i < m_table_size; i++)
		{
			if(m_table_pointer[i] == 0)
			{
				m_table_pointer[i] = pointer;
				return true;
			}
		}
		return false;
	}

	/* Removes pointer from pool, returns false if not found */
	bool removePointer(void* pointer)
	{
		for(unsigned i = 0; i < m_table_size; i++)
		{
			if(m_table_pointer[i] == pointer)
			{
				m_table_pointer[i] = 0;
				return true;
			}
		}
		return false;
	}

	/* Allocates a new memory block, returns NULL on failure */
	void* create(unsigned size)
	{
		char* ptr = static_cast<char*>(calloc(size + 20, 1));
		if(!ptr)
			return 0;

		MemMeta mm = {char(20 - (unsigned(ptr + 4) & 15)), size};
		ptr += mm.offset;
		reinterpret_cast<MemMeta*>(ptr)[-1] = mm;

		if(!addPointer(ptr))
		{
			destroy(ptr, true);
			return 0;
		}

		return ptr;
	}

	/* Frees a memory block, only and only if it's part of the pool */
	void destroy(void* pointer, bool found)
	{
		if(!pointer)
			return;

		if(found || removePointer(pointer))
		{
			char* ptr = static_cast<char*>(pointer);
			MemMeta mm = reinterpret_cast<MemMeta*>(ptr)[-1];
			free(ptr - mm.offset);
		}
	}

public:
	MemPool(unsigned size) : m_table_size(size)
	{
		m_table_pointer = static_cast<void**>(calloc(m_table_size, sizeof(void*)));
		if(!m_table_pointer)
			abort();
	}

	~MemPool()
	{
		for(unsigned i = 0; i < m_table_size; i++)
			destroy(m_table_pointer[i], true);

		free(m_table_pointer);
	}

	friend void* r3vMalloc(unsigned);
	friend void r3vFree(void*);
	friend long long r3vGetMemoryUsage();
};

//Memory pool instance
static MemPool MM_POOL(16384);

//external memory functions
R3VAPI void* r3vMalloc(unsigned size){return MM_POOL.create(size);}
R3VAPI void r3vFree(void* pointer){MM_POOL.destroy(pointer, false);}

R3VAPI long long r3vGetMemoryUsage()
{
	long long total = 0;
	for(unsigned i = 0; i < MM_POOL.m_table_size; i++)
	{
		char* ptr = static_cast<char*>(MM_POOL.m_table_pointer[i]);
		if(ptr)
			total += reinterpret_cast<MemPool::MemMeta*>(ptr)[-1].size;
	}
	return total;
}
