#pragma once

/*
 * IMonitor implementation
 */
class CMonitor : public r3dVoxel::IMonitor
{
	GLFWmonitor* m_monitor;

	static r3dVoxel::SVideoMode copyVideoMode(const GLFWvidmode& mode)
	{
		return
		{
			std::int16_t(mode.width),
			std::int16_t(mode.height),
			std::int8_t(mode.redBits),
			std::int8_t(mode.greenBits),
			std::int8_t(mode.blueBits),
			std::int8_t(mode.refreshRate)
		};
	}

public:
	CMonitor(GLFWmonitor* mon = nullptr) noexcept : m_monitor(mon) {}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::math::ivec getPosition()
	{
		std::int32_t x, y;
		glfwGetMonitorPos(m_monitor, &x, &y);
		return r3dVoxel::math::ivec{x, y, 0, 0};
	}

	r3dVoxel::math::ivec getPhysicalSize()
	{
		std::int32_t width, height;
		glfwGetMonitorPhysicalSize(m_monitor, &width, &height);
		return r3dVoxel::math::ivec{width, height, 0, 0};
	}

	const char* getName()
	{
		return glfwGetMonitorName(m_monitor);
	}

	r3dVoxel::SVideoMode getVideoMode()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		if(mode)
			return copyVideoMode(*mode);
		else
			return {0};
	}

	r3dVoxel::Array<r3dVoxel::SVideoMode> getAllVideoModes()
	{
		std::int32_t count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, &count);

		try
		{
			decltype(getAllVideoModes()) modes(count);
			while(count--)
				modes[count] = copyVideoMode(pvm[count]);
			return modes;
		}
		catch(...)
		{
			return {};
		}
	}
};
