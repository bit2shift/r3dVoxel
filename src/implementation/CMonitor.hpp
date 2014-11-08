/*
 * IMonitor implementation
 */
class CMonitor : public r3dVoxel::IMonitor
{
	GLFWmonitor* m_monitor;
	r3dVoxel::SVideoMode* m_modes;

private:
	static void copyVideoMode(r3dVoxel::SVideoMode* vm, const GLFWvidmode* mode)
	{
		vm->valid   = 1;
		vm->width   = mode->width;
		vm->height  = mode->height;
		vm->red     = mode->redBits;
		vm->green   = mode->greenBits;
		vm->blue    = mode->blueBits;
		vm->refresh = mode->refreshRate;
	}

public:
	CMonitor(GLFWmonitor* mon) : m_monitor(mon), m_modes(0) {}

	~CMonitor()
	{
		if(m_modes)
			delete[] m_modes;
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	/* CDT doesn't like the subscript on vector types */
	r3dVoxel::math::ivec2 getPosition()
	{
		r3dVoxel::math::ivec2 pos;
		glfwGetMonitorPos(m_monitor, &pos[0], &pos[1]);
		return pos;
	}

	/* CDT doesn't like the subscript on vector types */
	r3dVoxel::math::uvec2 getPhysicalSize()
	{
		r3dVoxel::math::ivec2 size;
		glfwGetMonitorPhysicalSize(m_monitor, &size[0], &size[1]);
		return (r3dVoxel::math::uvec2)size;
	}

	const char* getName()
	{
		return glfwGetMonitorName(m_monitor);
	}

	const r3dVoxel::SVideoMode getVideoMode()
	{
		r3dVoxel::SVideoMode vm = {0};
		const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
		if(mode)
			copyVideoMode(&vm, mode);
		return vm;
	}

	const r3dVoxel::SVideoMode* getAllVideoModes()
	{
		//get available video modes
		int count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, &count);

		//deallocate old array, if existed
		if(m_modes)
			delete[] m_modes;

		//allocate new array, with 1 extra slot, NULL if it fails (nothrow)
		m_modes = new (std::nothrow) r3dVoxel::SVideoMode[count + 1]();
		if(m_modes)
		{
			while(count--)
				copyVideoMode(&m_modes[count], &pvm[count]);
		}

		return m_modes;
	}
};
