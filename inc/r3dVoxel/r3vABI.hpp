#pragma once

#include <cstddef>

#ifdef R3V_EXPORT
#define R3VAPI extern "C" [[gnu::dllexport]]
#else
#define R3VAPI extern "C" [[gnu::dllimport]]
#endif

namespace r3dVoxel
{
	class IGameEngine;
	class ILogger;
}

/*
 * Initialize game engine
 * Consecutive calls will return the same instance.
 */
R3VAPI r3dVoxel::IGameEngine* r3vInitialize();

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
 * Obtain named logger instance
 * All instances are destroyed upon exit.
 */
R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name, const char* fname = nullptr);
