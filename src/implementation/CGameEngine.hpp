/*
 * IGameEngine implementation
 */
class CGameEngine : public r3dVoxel::IGameEngine
{
	bool m_monitorTrigger;

public:
	CGameEngine(GLFWmonitorfun callback) : m_monitorTrigger(false)
	{
		//set singleton
		THE_GAME_ENGINE = this;

		//init GLFW
		if(!glfwInit())
			throw 0;

		//set monitor callback
		glfwSetMonitorCallback(callback);
	}

	~CGameEngine()
	{
		//unset monitor callback and stop GLFW
		glfwSetMonitorCallback(0);
		glfwTerminate();

		//unset singleton
		THE_GAME_ENGINE = 0;
	}

	void setTrigger(){m_monitorTrigger = true;}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	r3dVoxel::IClassArray* getAllMonitors()
	{
		//get connected monitors
		int count = 0;
		GLFWmonitor** pmon = glfwGetMonitors(&count);
		if(!pmon)
			return 0;

		//allocate new array, NULL if it fails
		r3dVoxel::IClassArray* monitors = r3vNewClassArray(count);
		if(monitors)
		{
			while(count--)
				monitors->at(count) = new CMonitor(pmon[count]);
		}

		return monitors;
	}

	r3dVoxel::IMonitor* getPrimaryMonitor()
	{
		return new CMonitor(glfwGetPrimaryMonitor());
	}

	bool monitorsHaveChanged()
	{
		bool flag = m_monitorTrigger;
		m_monitorTrigger = false;
		return flag;
	}

	r3dVoxel::IView* createView()
	{
		//TODO finish
		return 0;
	}
};

/*
 * GLFW callback used to notify about monitor events
 */
void r3vMonitorCallback(GLFWmonitor* monitor, int event)
{
	/* We **know** it's an object of CGameEngine */
	static_cast<CGameEngine*>(THE_GAME_ENGINE)->setTrigger();
}

R3VAPI r3dVoxel::IGameEngine* r3vInitialize()
{
	//Return current instance if engine is already initialized
	if(THE_GAME_ENGINE)
		return THE_GAME_ENGINE;

	try
	{
		return new CGameEngine(r3vMonitorCallback);
	}
	catch(...){}
	return 0;
}
