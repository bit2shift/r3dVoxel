#include "Pool.hpp"
#include <atomic>

/*
 * Exporting the library functions from here,
 * so mirror the following define in here
 */
#define R3VAPI         extern "C" [[gnu::dllexport]]
#define THREAD_LOCK    volatile simple_mutex sm

/*
 * This gets constructed upon library loading
 * and then destroyed upon unloading.
 * Standard behaviour for DLL and SO
 */
static Pool MEMORY_POOL;
static std::atomic_flag MEMORY_LOCK = ATOMIC_FLAG_INIT;

struct simple_mutex
{
	simple_mutex() { while(MEMORY_LOCK.test_and_set(std::memory_order_acquire)); }
	~simple_mutex(){       MEMORY_LOCK.clear(std::memory_order_release);         }
};

R3VAPI void* r3vMalloc(std::size_t size)
{
	THREAD_LOCK;
	return MEMORY_POOL.create(size);
}

R3VAPI void r3vFree(void* pointer)
{
	THREAD_LOCK;
	MEMORY_POOL.destroy(pointer);
}

R3VAPI std::size_t r3vGetMemoryUsage()
{
	THREAD_LOCK;
	return MEMORY_POOL.usage();
}
