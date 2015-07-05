#pragma once

/*
 * Memory management functions:
 * - Allocation
 * - Deallocation
 * - Total allocated memory
 * - Size of allocation
 */
R3VAPI void* r3vMalloc(std::size_t size);
R3VAPI void r3vFree(void* pointer);
R3VAPI std::size_t r3vGetMemoryUsage();
R3VAPI std::size_t r3vGetSize(const void* pointer);

/*
 * Overridden memory operators
 * These 4 operators are used by the other variants
 */
void* operator new(std::size_t size)
{
	void* pointer = r3vMalloc(size);
	if(pointer)
		return pointer;
	else
		throw std::bad_alloc();
}

void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
	return r3vMalloc(size);
}

void operator delete(void* pointer) noexcept
{
	r3vFree(pointer);
}

void operator delete(void* pointer, const std::nothrow_t&) noexcept
{
	r3vFree(pointer);
}
