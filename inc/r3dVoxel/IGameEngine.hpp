#pragma once

#include "IClass.hpp"
#include "util/Array.hpp"

namespace r3dVoxel
{
	class IMonitor;
	class IView;

	/*
	 * The most important interface of r3dVoxel
	 */
	class IGameEngine : public IClass
	{
	public:
		/////////////////////////
		//// MONITOR SECTION ////
		/////////////////////////

		/*
		 * Query connected monitors
		 * Returns an array of IMonitor, empty on failure.
		 */
		virtual util::Array<IMonitor*> getAllMonitors() noexcept = 0;

		/* Returns the primary monitor or nullptr on failure */
		virtual IMonitor* getPrimaryMonitor() noexcept = 0;


		//////////////////////
		//// VIEW SECTION ////
		//////////////////////

		virtual IView* createView(/* TODO add parameters */) noexcept = 0;

		//TODO add relevant methods
	};
}
