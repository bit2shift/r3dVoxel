/*
 * IMonitor implementation
 */
class CMonitor : public r3dVoxel::IMonitor
{
	GLFWmonitor* m_monitor;

private:
	static void copyVideoMode(r3dVoxel::SVideoMode& vm, const GLFWvidmode& mode)
	{
		vm.width   = mode.width;
		vm.height  = mode.height;
		vm.red     = mode.redBits;
		vm.green   = mode.greenBits;
		vm.blue    = mode.blueBits;
		vm.refresh = mode.refreshRate;
	}

public:
	CMonitor(GLFWmonitor* mon) : m_monitor(mon) {}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::math::ivec2 getPosition()
	{
		int x, y;
		glfwGetMonitorPos(m_monitor, &x, &y);
		r3dVoxel::math::ivec2 pos = {x, y};
		return pos;
	}

	r3dVoxel::math::ivec2 getPhysicalSize()
	{
		int width, height;
		glfwGetMonitorPhysicalSize(m_monitor, &width, &height);
		r3dVoxel::math::ivec2 size = {width, height};
		return size;
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

	r3dVoxel::IBasicArray<r3dVoxel::SVideoMode>* getAllVideoModes()
	{
		//get available video modes
		int count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, &count);

		//allocate new array, NULL if it fails
		r3dVoxel::IBasicArray<r3dVoxel::SVideoMode>* modes = r3vNewBasicArray<r3dVoxel::SVideoMode>(count);
		if(modes)
		{
			while(count--)
				copyVideoMode(modes->at(count), pvm[count]);
		}

		return modes;
	}
};
