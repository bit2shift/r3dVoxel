#pragma once

/*
 * IGameEngine implementation
 */
class CGameEngine : public r3dVoxel::IGameEngine
{
	std::map<GLFWmonitor*, CMonitor> m_monitors;

	CGameEngine()
	{
		glfwSetErrorCallback(error_callback);

		if(!glfwInit())
			throw std::runtime_error("GLFW initialization failure");

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
	}

	static void error_callback(std::int32_t error, const char* description)
	{
		r3vGetLogger(nullptr)->log(r3dVoxel::ELoggingLevel::SEVERE, "GLFW Error {0:X8} : {1}", error, description);
	}

	static void monitor_callback(GLFWmonitor* monitor, std::int32_t status)
	{
		CGameEngine* engine = static_cast<CGameEngine*>(r3vInitialize());
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

public:
	friend r3dVoxel::IGameEngine* r3vInitialize() try
	{
		static CGameEngine instance;
		return &instance;
	}
	catch(std::exception& e)
	{
		r3vGetLogger(nullptr)->log(r3dVoxel::ELoggingLevel::SEVERE, "r3vInitialize() : {0}", e.what());
		return nullptr;
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
