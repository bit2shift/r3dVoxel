#pragma once

#include "../r3vABI.hpp"

#include <cstddef>
#include <new>

/*
 * 1) Non-array operator new. Base version.
 */
void* operator new(std::size_t size)
{
	while(true)
	{
		if(auto pointer = r3vMalloc(size))
			return pointer;

		if(auto handler = std::get_new_handler())
			handler();
		else
			throw std::bad_alloc();
	}
}

/*
 * 2) Array operator new. Calls version (1).
 */
void* operator new[](std::size_t size)
{
	return ::operator new(size);
}

/*
 * 3) Non-throwing non-array operator new. Calls version (1).
 */
void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
	try
	{
		return ::operator new(size);
	}
	catch(std::bad_alloc&)
	{
		return nullptr;
	}
}

/*
 * 4) Non-throwing array operator new. Calls version (2).
 */
void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
	try
	{
		return ::operator new[](size);
	}
	catch(std::bad_alloc&)
	{
		return nullptr;
	}
}
