#pragma once

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

	/* Derived classes */
	#include "r3dVoxel/IBasicArray.hpp"
	#include "r3dVoxel/IClassArray.hpp"
	#include "r3dVoxel/IMonitor.hpp"
	#include "r3dVoxel/IView.hpp"
	#include "r3dVoxel/IGameEngine.hpp"

	//TODO more interfaces
}

/*
 * Factory for arrays of all basic types (scalars/pod)
 * Class types may cause unspecified behavior
 */
template<typename T>
r3dVoxel::IBasicArray<T>* r3vNewBasicArray(unsigned length) R3VAPI;

/*
 * Factory for arrays of IClass objects
 * This IArray implementation calls IClass::release() for each element on IArray::release()
 */
template<typename T>
r3dVoxel::IClassArray<T>* r3vNewClassArray(unsigned length) R3VAPI;

/* Initialize game engine */
r3dVoxel::IGameEngine* r3vInitialize() R3VAPI;
