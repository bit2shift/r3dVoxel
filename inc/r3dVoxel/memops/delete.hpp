#pragma once

#include "../r3vABI.hpp"

#include <cstddef>
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
	::operator delete(pointer);
}

/*
 * 3) Non-array operator delete called by version (3) of operator new if constructor throws.
 */
void operator delete(void* pointer, const std::nothrow_t&) noexcept
{
	::operator delete(pointer);
}

/*
 * 4) Array operator delete called by version (4) of operator new if constructor throws.
 */
void operator delete[](void* pointer, const std::nothrow_t&) noexcept
{
	::operator delete[](pointer);
}

/*
 * Versions (5) and (6) are considered defects in our allocation model.
 * Versions (7) and (8) were removed as stated in LWG 2458.
 * > http://open-std.org/JTC1/SC22/WG21/docs/lwg-defects.html#2458
 * We don't sort allocations by their size.
 * WE SORT THEM BY THEIR POINTER IN A HASHTABLE!
 */

/*
 * 5) Sized version of 1)
 */
void operator delete(void* pointer, std::size_t) noexcept
{
	::operator delete(pointer);
}

/*
 * 6) Sized version of 2)
 */
void operator delete[](void* pointer, std::size_t) noexcept
{
	::operator delete[](pointer);
}
