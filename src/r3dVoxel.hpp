#pragma once

namespace r3dVoxel
{
	/* Basic stuff */
	#include "r3dVoxel/Definitions.hpp"
	#include "r3dVoxel/Array.hpp"
	#include "r3dVoxel/SVideoMode.hpp"

	/* Math stuff */
	namespace math
	{
		#include "r3dVoxel/math/Vector.hpp"
		//TODO more math stuff
	};

	/* OOP base stuff */
	#include "r3dVoxel/IClass.hpp"
	#include "r3dVoxel/Ref.hpp"
	#include "r3dVoxel/RefArray.hpp"

	/* Derived classes */
	#include "r3dVoxel/IMonitor.hpp"
	#include "r3dVoxel/IView.hpp"
	#include "r3dVoxel/IGameEngine.hpp"

	//TODO more interfaces
};

R3VAPI r3dVoxel::IGameEngine* r3vInitialize();
