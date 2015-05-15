#include <cstdlib>
#include "Pool.hpp"

/*
 * Exporting the library functions from here,
 * so mirror the following define in here
 */
#define R3VAPI    extern "C" [[gnu::dllexport]]

static Pool MEMORY_POOL;

R3VAPI void* r3vMalloc(std::size_t size)
{
	return MEMORY_POOL.create(size);
}

R3VAPI void r3vFree(void* pointer)
{
	MEMORY_POOL.destroy(pointer);
}

R3VAPI std::size_t r3vGetMemoryUsage()
{
	return MEMORY_POOL.usage();
}
