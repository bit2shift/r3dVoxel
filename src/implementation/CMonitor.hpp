/*
 * IMonitor implementation
 */
class CMonitor : public r3dVoxel::IMonitor
{
	GLFWmonitor* m_monitor;

private:
	static void copyVideoMode(r3dVoxel::SVideoMode& vm, const GLFWvidmode& mode)
	{
		vm.width   = short(mode.width);
		vm.height  = short(mode.height);
		vm.red     = char(mode.redBits);
		vm.green   = char(mode.greenBits);
		vm.blue    = char(mode.blueBits);
		vm.refresh = char(mode.refreshRate);
	}

public:
	CMonitor() : m_monitor(0) {}
	CMonitor(GLFWmonitor* mon) : m_monitor(mon) {}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::math::ivec getPosition() const
	{
		int x, y;
		glfwGetMonitorPos(m_monitor, &x, &y);
		r3dVoxel::math::ivec pos = {x, y, 0, 0};
		return pos;
	}

	r3dVoxel::math::ivec getPhysicalSize() const
	{
		int width, height;
		glfwGetMonitorPhysicalSize(m_monitor, &width, &height);
		r3dVoxel::math::ivec size = {width, height, 0, 0};
		return size;
	}

	const char* getName() const
	{
		return glfwGetMonitorName(m_monitor);
	}

	r3dVoxel::SVideoMode getVideoMode() const
	{
		r3dVoxel::SVideoMode vm = {0};
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		if(mode)
			copyVideoMode(vm, *mode);

		return vm;
	}

	r3dVoxel::IByteArray* getAllVideoModes() const
	{
		//get available video modes
		int count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, &count);
		if(!pvm)
			return 0;

		//allocate new array
		r3vArrayHelper<r3dVoxel::SVideoMode> modes(count);
		if(modes.array)
		{
			while(count--)
				copyVideoMode(modes[count], pvm[count]);
		}

		//can return NULL
		return modes.array;
	}
};
