/*
 * IMonitor implementation
 */
class CMonitor : public r3dVoxel::IMonitor
{
	GLFWmonitor* m_monitor;

private:
	static void copyVideoMode(r3dVoxel::SVideoMode* vm, const GLFWvidmode* mode)
	{
		vm->width   = mode->width;
		vm->height  = mode->height;
		vm->red     = mode->redBits;
		vm->green   = mode->greenBits;
		vm->blue    = mode->blueBits;
		vm->refresh = mode->refreshRate;
	}

public:
	CMonitor(GLFWmonitor* mon) : m_monitor(mon) {}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::math::ivec2 getPosition()
	{
		r3dVoxel::math::ivec2 pos;
		glfwGetMonitorPos(m_monitor, (int*)&pos[0], (int*)&pos[1]);
		return pos;
	}

	r3dVoxel::math::uvec2 getPhysicalSize()
	{
		r3dVoxel::math::uvec2 size;
		glfwGetMonitorPhysicalSize(m_monitor, (int*)&size[0], (int*)&size[1]);
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
			copyVideoMode(&vm, mode);
		return vm;
	}

	r3dVoxel::IArray* getAllVideoModes()
	{
		//get available video modes
		int count = 0;
		const GLFWvidmode* pvm = glfwGetVideoModes(m_monitor, &count);

		//allocate new array, NULL if it fails
		//sizeof(SVideoMode) == sizeof(long long) == 8 bytes
		r3dVoxel::IArray* modes = r3vNewArray(r3dVoxel::ArrayTypes::LONG, count);
		if(modes)
		{
			while(count--)
				copyVideoMode((r3dVoxel::SVideoMode*)modes->raw(count), &pvm[count]);
		}

		return modes;
	}
};
