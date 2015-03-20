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
 * Consecutive calls will return the same instance.
 */
R3VAPI r3dVoxel::IGameEngine* r3vInitialize();

/*
 * Factory for the byte array.
 */
R3VAPI r3dVoxel::IByteArray* r3vNewByteArray(unsigned length);

/*
 * Factory for arrays of IClass objects
 * This array calls r3dVoxel::IClass::release() for each element on release
 */
R3VAPI r3dVoxel::IClassArray* r3vNewClassArray(unsigned length);

/*
 * Wrapper template for r3dVoxel::IByteArray
 * DO NOT USE THIS FOR ARRAYS OF DERIVED CLASSES OF r3dVoxel::IClass
 * r3dVoxel::IClass and its derivatives are INTERFACES!
 * As such, they use r3dVoxel::IClass::release() for deallocation.
 *
 * Regular classes can be safely used, with some caution in mind.
 * DO NOT USE VIRTUAL CLASSES, SEGMENTATION FAULT WILL OCCUR ON DEALLOCATION!
 */
template<typename T>
class r3vArrayHelper : virtual r3dVoxel::Final
{
public:
	typedef typename r3dVoxel::Const<T, r3dVoxel::IByteArray>::type ByteArray;
	ByteArray* array;

	/* Allocate array for "num" elements */
	r3vArrayHelper(const unsigned num) : array(r3vNewByteArray(num * sizeof(T))) {}

	/* Creates helper instance with existing array */
	r3vArrayHelper(ByteArray* ptr) : array(ptr) {}

	/* Calls T::~T() for each element in the array */
	void release() const
	{
		for(unsigned i = 0; i < array->length(); i += sizeof(T))
			static_cast<T*>(array->at(i))->~T();

		array->release();
	}

	/* Returns the number of elements in the array */
	unsigned length() const
	{
		return (array->length() / sizeof(T));
	}

	/* Accesses an element in the array */
	T& operator[](unsigned index)
	{
		return *static_cast<T*>(array->at(index * sizeof(T)));
	}

	/* Accesses a const element in the array */
	const T operator[](unsigned index) const
	{
		return *static_cast<T*>(array->at(index * sizeof(T)));
	}
};
