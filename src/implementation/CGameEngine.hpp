/* forward declaration */
static r3dVoxel::IGameEngine* init(bool);

/*
 * IGameEngine implementation
 */
class CGameEngine : public r3dVoxel::IGameEngine
{
	typedef std::map<GLFWmonitor*, CMonitor> mon;
	mon m_monitors;

	static void monitor_callback(GLFWmonitor* monitor, int status)
	{
		CGameEngine* engine = static_cast<CGameEngine*>(r3vInitialize());
		if(engine)
		{
			switch(status)
			{
			case GLFW_CONNECTED:
				engine->m_monitors[monitor] = CMonitor(monitor);
				break;

			case GLFW_DISCONNECTED:
				engine->m_monitors.erase(monitor);
				break;
			}
		}
	}

public:
	CGameEngine()
	{
		//init GLFW
		if(!glfwInit())
			throw 0;

		//set monitor callback
		glfwSetMonitorCallback(monitor_callback);

		//get all monitors into our map
		int count = 0;
		GLFWmonitor** pmon = glfwGetMonitors(&count);
		for(int i = 0; i < count; i++)
			m_monitors[pmon[i]] = CMonitor(pmon[i]);
	}

	~CGameEngine()
	{
		glfwTerminate();
		init(true);
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	const r3dVoxel::IByteArray* getAllMonitors()
	{
		//this is an exceptional use case
		r3vArrayHelper<r3dVoxel::IMonitor*> pmon(m_monitors.size());
		if(pmon.array)
		{
			int i = 0;
			for(mon::iterator m = m_monitors.begin(); m != m_monitors.end(); m++)
				pmon[i++] = &m->second;
		}

		//can return NULL
		return pmon.array;
	}

	const r3dVoxel::IMonitor* getPrimaryMonitor()
	{
		GLFWmonitor* pmon = glfwGetPrimaryMonitor();
		if(pmon && m_monitors.count(pmon))
			return &m_monitors[pmon];
		else
			return 0;
	}

	r3dVoxel::IView* createView()
	{
		//TODO finish
		return 0;
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
	static CGameEngine* instance = 0;

	if(reset)
		instance = 0;
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
				throw "Should have remained 0";
		}
	}

	return instance;
}
