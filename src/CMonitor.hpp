#pragma once

#include <r3dVoxel/IMonitor.hpp>
#include <r3dVoxel/math/Vector.hpp>
#include <r3dVoxel/util/Array.hpp>

#include <GLFW/glfw3.h>

namespace r3dVoxel
{
	/*
	 * IMonitor implementer
	 */
	class CMonitor : public IMonitor
	{
		GLFWmonitor* m_monitor;

	public:
		CMonitor(GLFWmonitor* mon) noexcept;

		///////////////////////////
		//// Interface methods ////
		///////////////////////////

		math::ivec getPosition() noexcept;
		math::ivec getPhysicalSize() noexcept;
		const char* getName() noexcept;
		SVideoMode getVideoMode() noexcept;
		util::Array<SVideoMode> getAllVideoModes() noexcept;
	};
}
