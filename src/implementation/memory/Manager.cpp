#include "Pool.hpp"

/*
 * Exporting the library functions from here,
 * so mirror the following define in here
 */
#define R3VAPI    extern "C" [[gnu::dllexport]]

/*
 * This gets constructed upon library loading
 * and then destroyed upon unloading.
 * Standard behaviour for DLL and SO
 */
static Pool MEMORY_POOL;

R3VAPI void* r3vMalloc(std::size_t size)
{
	return size ? MEMORY_POOL.create(size) : nullptr;
}

R3VAPI void r3vFree(void* pointer)
{
	pointer ? MEMORY_POOL.destroy(pointer) : (void)0;
}

R3VAPI std::size_t r3vGetMemoryUsage()
{
	return MEMORY_POOL.usage();
}
