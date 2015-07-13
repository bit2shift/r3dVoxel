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
#include <type_traits>      //std::conditional, std::is_integral
#include <utility>          //std::forward, ...

#if (__GNUG__ < 5) && !defined(__clang__)
#include "r3dVoxel/put_time.hpp"
#endif

#ifdef R3V_EXPORT
#define R3VAPI    extern "C" [[gnu::dllexport]]
#else
#define R3VAPI    extern "C" [[gnu::dllimport]]
#endif

#include "r3dVoxel/Memory.hpp"

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
R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name, const char* fname = nullptr);

/*
 * Initialize game engine
 * Consecutive calls will return the same instance.
 */
R3VAPI r3dVoxel::IGameEngine* r3vInitialize();
