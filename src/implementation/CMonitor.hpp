/*
 * IMonitor implementation
 */
class CMonitor : public r3dVoxel::IMonitor
{
	GLFWmonitor* m_monitor;

private:
	static void copyVideoMode(r3dVoxel::SVideoMode& vm, const GLFWvidmode mode)
	{
		vm.width   = std::int16_t(mode.width);
		vm.height  = std::int16_t(mode.height);
		vm.red     = std::int8_t(mode.redBits);
		vm.green   = std::int8_t(mode.greenBits);
		vm.blue    = std::int8_t(mode.blueBits);
		vm.refresh = std::int8_t(mode.refreshRate);
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
		r3dVoxel::SVideoMode vm = {0};
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		if(mode)
			copyVideoMode(vm, *mode);

		return vm;
	}

	r3dVoxel::Array<r3dVoxel::SVideoMode> getAllVideoModes()
	{
		//get available video modes
		std::int32_t count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, &count);

		//allocate new array, return empty on failure
		try
		{
			decltype(getAllVideoModes()) modes(count);
			while(count--)
				copyVideoMode(modes[count], pvm[count]);
			return modes;
		}
		catch(...)
		{
			return {};
		}
	}
};
