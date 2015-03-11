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
	#include "r3dVoxel/IByteArray.hpp"
	#include "r3dVoxel/IClassArray.hpp"
	#include "r3dVoxel/IMonitor.hpp"
	#include "r3dVoxel/IView.hpp"
	#include "r3dVoxel/IGameEngine.hpp"

	//TODO more interfaces
}

/*
 * Initialize game engine
 */
r3dVoxel::IGameEngine* r3vInitialize() R3VAPI;

/*
 * Factory for the byte array.
 */
r3dVoxel::IByteArray* r3vNewByteArray(unsigned length) R3VAPI;

/*
 * Factory for arrays of IClass objects
 * This array calls IClass::release() for each element on release
 */
template<typename T>
r3dVoxel::IClassArray<T>* r3vNewClassArray(unsigned length) R3VAPI;

/*
 * Wrapper template for r3dVoxel::IByteArray
 * DO NOT USE THIS FOR ARRAYS OF DERIVED CLASSES OF r3dVoxel::IClass
 * r3dVoxel::IClass and its derivatives are INTERFACES!
 * As such, they use r3dVoxel::IClass::release() for deallocation.
 */
template<typename T>
class r3vArrayHelper : virtual r3dVoxel::Final
{
public:
	r3dVoxel::IByteArray* array;

	/* Allocate array for "num" elements */
	r3vArrayHelper(unsigned num) : array(r3vNewByteArray(num * sizeof(T))) {}

	/* Creates helper instance with existing array */
	r3vArrayHelper(r3dVoxel::IByteArray* ptr) : array(ptr) {}

	/* Returns the number of elements in the array */
	unsigned length()
	{
		return (array->length() / sizeof(T));
	}

	/* Accesses an element in the array, beware of array bounds */
	T& operator[](unsigned index)
	{
		return static_cast<T*>(array->pointer())[index];
	}

	/* Calls T::~T() for each element in the array */
	void operator~()
	{
		unsigned count = length();
		while(count--)
			(*this)[count].~T();

		array->release();
	}
};
