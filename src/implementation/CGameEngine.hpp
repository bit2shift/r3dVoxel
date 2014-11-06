/*
 * GLFW callback used to notify about monitor events
 */
void r3vMonitorCallback(GLFWmonitor* monitor, int event)
{
	THE_GAME_ENGINE->getMonitors();
}

/*
 * IGameEngine implementation
 */
class CGameEngine : public r3dVoxel::IGameEngine
{
	r3dVoxel::IMonitor** m_monitors;

public:
	CGameEngine() : m_monitors(0)
	{
		THE_GAME_ENGINE = this;
		glfwSetMonitorCallback(r3vMonitorCallback);
	}

	~CGameEngine()
	{
		glfwSetMonitorCallback(0);
		THE_GAME_ENGINE = 0;

		//XXX game engine shutdown area

		if(m_monitors)
			delete[] m_monitors;

		glfwTerminate();
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::IMonitor** getMonitors()
	{
		//get connected monitors
		int count = 0;
		GLFWmonitor** pmon = glfwGetMonitors(&count);

		//deallocate old array, if existed
		if(m_monitors)
			delete[] m_monitors;

		//allocate new array, with 1 extra slot, NULL if it fails (nothrow)
		m_monitors = new (std::nothrow) r3dVoxel::IMonitor*[count + 1]();
		if(m_monitors)
		{
			while(count--)
				m_monitors[count] = new CMonitor(pmon[count]);
		}

		return m_monitors;
	}

	r3dVoxel::IMonitor* getPrimaryMonitor()
	{
		return new CMonitor(glfwGetPrimaryMonitor());
	}

	r3dVoxel::IView* createView()
	{
		//TODO finish
		return 0;
	}
};

R3VAPI r3dVoxel::IGameEngine* r3vInitialize()
{
	//Return current instance if engine is already initialized
	if(THE_GAME_ENGINE)
		return THE_GAME_ENGINE;

	//Initialize GLFW, return NULL if it fails
	if(!glfwInit())
		return 0;

	//XXX hmm idk, but can have other stuff in here
	return new CGameEngine();
}
