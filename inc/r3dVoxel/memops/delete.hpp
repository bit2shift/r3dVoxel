#pragma once

#include "../r3vABI.hpp"

#include <cstddef>
#include <new>

/*
 * 1) Non-array operator delete.
 */
void operator delete(void* pointer) noexcept
{
	r3vFree(pointer, 0);
}

/*
 * 2) Array operator delete.
 */
void operator delete[](void* pointer) noexcept
{
	r3vFree(pointer, 0);
}

/*
 * 3) Non-array operator delete called by version (3) of operator new if constructor throws.
 */
void operator delete(void* pointer, const std::nothrow_t&) noexcept
{
	r3vFree(pointer, 0);
}

/*
 * 4) Array operator delete called by version (4) of operator new if constructor throws.
 */
void operator delete[](void* pointer, const std::nothrow_t&) noexcept
{
	r3vFree(pointer, 0);
}

/*
 * Versions (5) through (8) are considered defects in our allocation model.
 * We don't sort allocations by their size.
 * WE SORT THEM BY THEIR POINTER IN A HASHTABLE!
 */

/*
 * 5) Sized version of 1)
 */
void operator delete(void* pointer, std::size_t size) noexcept
{
	r3vFree(pointer, size);
}

/*
 * 6) Sized version of 2)
 */
void operator delete[](void* pointer, std::size_t size) noexcept
{
	r3vFree(pointer, size);
}

/*
 * 7) Sized version of 3)
 */
void operator delete(void* pointer, std::size_t size, const std::nothrow_t&) noexcept
{
	r3vFree(pointer, size);
}

/*
 * 8) Sized version of 4)
 */
void operator delete[](void* pointer, std::size_t size, const std::nothrow_t&) noexcept
{
	r3vFree(pointer, size);
}
