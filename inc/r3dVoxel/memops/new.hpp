#pragma once

#include "../r3vABI.hpp"

#include <cstddef>
#include <new>

/*
 * 1) Non-array operator new. Called by (2).
 */
void* operator new(std::size_t size)
{
	while(true)
	{
		void* pointer = r3vMalloc(size);
		if(pointer)
			return pointer;

		std::new_handler handler = std::get_new_handler();
		if(handler)
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
 * 3) Non-throwing non-array operator new. Called by (4).
 */
void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
	while(true)
	{
		void* pointer = r3vMalloc(size);
		if(pointer)
			return pointer;

		std::new_handler handler = std::get_new_handler();
		if(handler)
			handler();
		else
			return nullptr;
	}
}

/*
 * 4) Non-throwing array operator new. Calls version (3).
 */
void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
	return ::operator new(size, std::nothrow);
}
