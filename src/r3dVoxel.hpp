#pragma once
#include <algorithm>        //std::copy
#include <cstdint>          //std::int8_t, std::uint8_t, ...
#include <initializer_list> //ditto
#include <new>              //std::size_t, std::bad_alloc, std::nothrow_t
#include <stdexcept>        //std::out_of_range

#ifdef R3V_EXPORT
#define R3VAPI    extern "C" [[gnu::dllexport]]
#else
#define R3VAPI    extern "C" [[gnu::dllimport]]
#endif

/*
 * Memory management functions
 * Used by overridden operators 'new' and 'delete'
 */
R3VAPI void* r3vMalloc(std::size_t size);
R3VAPI void r3vFree(void* pointer);
R3VAPI std::size_t r3vGetMemoryUsage();

/*
 * Overridden memory operators
 * These 4 operators are used by the other variants
 */
void* operator new(std::size_t size)
{
	void* ptr = r3vMalloc(size);
	if(ptr)
		return ptr;
	else
		throw std::bad_alloc();
}

void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{ return r3vMalloc(size); }

void operator delete(void* ptr) noexcept
{ r3vFree(ptr); }

[[gnu::alias("_ZdlPv")]]  //alias of "function delete pointer void" aka "operator delete(void*)"
void operator delete(void* ptr, const std::nothrow_t&) noexcept;

/*
 * The namespace
 */
namespace r3dVoxel
{
	/* Basic stuff */
	#include "r3dVoxel/Definitions.hpp"
	#include "r3dVoxel/SVideoMode.hpp"

	/* Math stuff */
	namespace math
	{
		#include "r3dVoxel/math/Vector.hpp"
		//TODO more math stuff
	}

	/* OOP base stuff */
	#include "r3dVoxel/IClass.hpp"
	#include "r3dVoxel/Ref.hpp"
	#include "r3dVoxel/Array.hpp"

	/* Derived classes */
	#include "r3dVoxel/IMonitor.hpp"
	#include "r3dVoxel/IView.hpp"
	#include "r3dVoxel/IGameEngine.hpp"

	//TODO more interfaces
}

/*
 * Initialize game engine
 * Consecutive calls will return the same instance.
 */
R3VAPI r3dVoxel::IGameEngine* r3vInitialize();

//TODO change terminate handler to release allocated memory
