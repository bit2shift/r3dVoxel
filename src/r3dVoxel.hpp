#pragma once
#include <algorithm>        //std::copy
#include <cmath>            //std::abs, std::signbit
#include <cstddef>          //std::size_t
#include <cstdint>          //std::int8_t, std::uint8_t, ...
#include <initializer_list> //ditto
#include <iomanip>          //IO manipulators
#include <new>              //std::bad_alloc, std::nothrow_t
#include <regex>            //std::regex, ...
#include <sstream>          //std::ostringstream
#include <stdexcept>        //std::out_of_range
#include <utility>          //std::forward, ...

#ifdef R3V_EXPORT
#define R3VAPI    extern "C" [[gnu::dllexport]]
#else
#define R3VAPI    extern "C" [[gnu::dllimport]]
#endif

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

/*
 * The namespace
 */
namespace r3dVoxel
{
	/* Basic stuff */
	#include "r3dVoxel/Definitions.hpp"
	#include "r3dVoxel/Array.hpp"

	/* Math stuff */
	namespace math
	{
		#include "r3dVoxel/math/Vector.hpp"
		//TODO more math stuff
	}

	/* OOP base class */
	#include "r3dVoxel/IClass.hpp"

	/* Derived classes */
	#include "r3dVoxel/ILogger.hpp"
	#include "r3dVoxel/IMonitor.hpp"
	#include "r3dVoxel/IView.hpp"
	#include "r3dVoxel/IGameEngine.hpp"

	//TODO more interfaces
}

/*
 * Obtain named logger instance
 * All instances are destroyed upon exit
 */
R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name);

/*
 * Initialize game engine
 * Consecutive calls will return the same instance.
 */
R3VAPI r3dVoxel::IGameEngine* r3vInitialize();
