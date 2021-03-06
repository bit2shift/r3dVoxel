#include "CMonitor.hpp"

#include "CLogger.hpp"

#include <r3dVoxel/ILogger.hpp>
#include <r3dVoxel/IMonitor.hpp>
#include <r3dVoxel/math/Vector.hpp>
#include <r3dVoxel/util/Array.hpp>
#include <r3dVoxel/util/parameter_pack.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cstdint>
#include <exception>

namespace r3dVoxel
{
	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	math::ivec CMonitor::getPosition() const noexcept
	{
		int x, y;
		glfwGetMonitorPos(m_monitor, &x, &y);
		return math::ivec{x, y, 0, 0};
	}

	math::ivec CMonitor::getPhysicalSize() const noexcept
	{
		int width, height;
		glfwGetMonitorPhysicalSize(m_monitor, &width, &height);
		return math::ivec{width, height, 0, 0};
	}

	const char* CMonitor::getName() const noexcept
	{
		return glfwGetMonitorName(m_monitor);
	}

	//Want Speed? Pass by Value.
	inline static SVideoMode copyVideoMode(GLFWvidmode mode)
	{
		return util::parameter_pack::list_cast<SVideoMode, std::uint16_t, std::uint16_t, std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>
		(mode.width, mode.height, mode.redBits, mode.greenBits, mode.blueBits, mode.refreshRate);
	}

	SVideoMode CMonitor::getVideoMode() const noexcept
	{
		if(auto mode = glfwGetVideoMode(m_monitor))
			return copyVideoMode(*mode);
		else
			return {};
	}

	util::Array<SVideoMode> CMonitor::getAllVideoModes() const noexcept
	{
		int cnt;
		auto ptr = glfwGetVideoModes(m_monitor, &cnt);

		try
		{
			util::Array<SVideoMode> arr{unsigned(cnt)};
			std::transform(ptr, (ptr + cnt), arr.begin(), copyVideoMode);
			return arr;
		}
		catch(std::exception& e)
		{
			CLogger("CMonitor")->log(ELoggingLevel::SEVERE, "{0}() : {1}", __func__, e.what());
			return {};
		}
	}
}
