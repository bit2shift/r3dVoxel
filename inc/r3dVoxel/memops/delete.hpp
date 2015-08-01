#pragma once

#include "../r3vABI.hpp"

#include <new>

/*
 * 1) Non-array operator delete.
 */
void operator delete(void* pointer) noexcept
{
	r3vFree(pointer);
}

/*
 * 2) Array operator delete.
 */
void operator delete[](void* pointer) noexcept
{
	r3vFree(pointer);
}

/*
 * 3) Non-array operator delete called by version (3) of operator new if constructor throws.
 */
void operator delete(void* pointer, const std::nothrow_t&) noexcept
{
	r3vFree(pointer);
}

/*
 * 4) Array operator delete called by version (4) of operator new if constructor throws.
 */
void operator delete[](void* pointer, const std::nothrow_t&) noexcept
{
	r3vFree(pointer);
}

/*
 * Versions (5) through (8) are considered defects in our allocation model.
 * We don't sort allocations by their size.
 * WE SORT THEM BY THEIR POINTER IN A HASHTABLE!
 */
