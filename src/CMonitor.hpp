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

		math::ivec getPosition() const noexcept;
		math::ivec getPhysicalSize() const noexcept;
		const char* getName() const noexcept;
		SVideoMode getVideoMode() const noexcept;
		util::Array<SVideoMode> getAllVideoModes() const noexcept;
	};
}
