#include "CMonitor.hpp"

#include <r3dVoxel/IMonitor.hpp>
#include <r3dVoxel/math/Vector.hpp>
#include <r3dVoxel/util/Array.hpp>
#include <r3dVoxel/util/parameter_pack.hpp>

#include <GLFW/glfw3.h>

#include <cstddef>
#include <cstdint>

namespace r3dVoxel
{
	CMonitor::CMonitor(GLFWmonitor* mon) noexcept : m_monitor(mon) {}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	math::ivec CMonitor::getPosition() noexcept
	{
		std::int32_t x, y;
		glfwGetMonitorPos(m_monitor, &x, &y);
		return math::ivec{x, y, 0, 0};
	}

	math::ivec CMonitor::getPhysicalSize() noexcept
	{
		std::int32_t width, height;
		glfwGetMonitorPhysicalSize(m_monitor, &width, &height);
		return math::ivec{width, height, 0, 0};
	}

	const char* CMonitor::getName() noexcept
	{
		return glfwGetMonitorName(m_monitor);
	}

	inline static SVideoMode copyVideoMode(const GLFWvidmode& mode)
	{
		return util::parameter_pack::list_cast<SVideoMode, std::int16_t, std::int16_t, std::int8_t, std::int8_t, std::int8_t, std::int8_t>
		(mode.width, mode.height, mode.redBits, mode.greenBits, mode.blueBits, mode.refreshRate);
	}

	SVideoMode CMonitor::getVideoMode() noexcept
	{
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		if(mode)
			return copyVideoMode(*mode);
		else
			return {};
	}

	util::Array<SVideoMode> CMonitor::getAllVideoModes() noexcept
	{
		std::size_t count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, reinterpret_cast<int*>(&count));

		try
		{
			util::Array<SVideoMode> modes(count);
			while(count--)
				modes[count] = copyVideoMode(pvm[count]);
			return modes;
		}
		catch(...)
		{
			return {};
		}
	}
}
