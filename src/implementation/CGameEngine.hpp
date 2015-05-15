/* forward declaration */
static r3dVoxel::IGameEngine* init(bool);

/*
 * IGameEngine implementation
 */
class CGameEngine : public r3dVoxel::IGameEngine
{
	std::map<GLFWmonitor*, CMonitor> m_monitors;

	static void monitor_callback(GLFWmonitor* monitor, std::int32_t status)
	{
		CGameEngine* engine = static_cast<CGameEngine*>(r3vInitialize());
		if(engine)
		{
			switch(status)
			{
			case GLFW_CONNECTED:
				engine->m_monitors.emplace(monitor, monitor);
				break;

			case GLFW_DISCONNECTED:
				engine->m_monitors.erase(monitor);
				break;
			}
		}
	}

public:
	CGameEngine() //TODO init glew
	{
		//init GLFW
		if(!glfwInit())
			throw std::runtime_error("GLFW initialization failure");

		//set monitor callback
		glfwSetMonitorCallback(monitor_callback);

		//get all monitors into our map
		std::int32_t count = 0;
		GLFWmonitor** pmon = glfwGetMonitors(&count);
		for(std::int32_t i = 0; i < count; i++)
			m_monitors.emplace(pmon[i], pmon[i]);
	}

	~CGameEngine()
	{
		glfwTerminate();
		init(true);
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::Array<r3dVoxel::IMonitor*> getAllMonitors()
	{
		try
		{
			std::size_t index = 0;
			decltype(getAllMonitors()) pmon(m_monitors.size());
			for(auto& m : m_monitors)
				pmon[index++] = &m.second;
			return pmon;
		}
		catch(...)
		{
			return {};
		}
	}

	r3dVoxel::IMonitor* getPrimaryMonitor()
	{
		GLFWmonitor* pmon = glfwGetPrimaryMonitor();
		if(pmon && m_monitors.count(pmon))
			return &m_monitors[pmon];
		else
			return nullptr;
	}

	r3dVoxel::IView* createView()
	{
		//TODO finish
		return nullptr;
	}
};

R3VAPI r3dVoxel::IGameEngine* r3vInitialize()
{
	return init(false);
}

/*
 * Initialization and singleton helper
 * internal function
 */
static r3dVoxel::IGameEngine* init(bool reset)
{
	static CGameEngine* instance = nullptr;

	if(reset)
		instance = nullptr;
	else if(!instance)
	{
		try
		{
			instance = new CGameEngine();
		}
		catch(...)
		{
			//sanity check
			if(instance)
				throw std::runtime_error("Should have been nullptr");
		}
	}

	return instance;
}
