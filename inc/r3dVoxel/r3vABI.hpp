#pragma once

#include "util/type_name.hpp"

#include <cstddef>

#if defined __ELF__
#define R3VAPI extern "C" [[gnu::visibility("default")]]
#elif defined R3V_EXPORT
#define R3VAPI extern "C" [[gnu::dllexport]]
#else
#define R3VAPI extern "C" [[gnu::dllimport]]
#endif

/*
 * Memory management functions:
 * - Allocation
 * - Deallocation
 * - Total allocated memory
 * - Size of allocation
 */
R3VAPI void* r3vMalloc(std::size_t size) noexcept;
R3VAPI void r3vFree(void* pointer) noexcept;
R3VAPI std::size_t r3vGetMemoryUsage() noexcept;
R3VAPI std::size_t r3vGetSize(const void* pointer) noexcept;

/*
 * Forward declaration
 * of classes used below
 */
namespace r3dVoxel
{
	class ILogger;
	class IGameEngine;
}

/*
 * Obtain named logger instance
 * All instances are destroyed upon exit.
 */
R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name) noexcept;

/*
 * Typed version of r3vGetLogger()
 */
template<typename T>
r3dVoxel::ILogger* r3vGetLogger()
{
	return r3vGetLogger(r3dVoxel::util::type_name<T>());
}

/*
 * Initialize game engine
 * Consecutive calls will return the same instance.
 */
R3VAPI r3dVoxel::IGameEngine* r3vInitialize() noexcept;
