#include "CGameEngine.hpp"

#include "CLogger.hpp"

#include <r3dVoxel/IGameEngine.hpp>
#include <r3dVoxel/ILogger.hpp>
#include <r3dVoxel/r3vABI.hpp>
#include <r3dVoxel/util/Array.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <exception>
#include <stdexcept>

namespace r3dVoxel
{
	void CGameEngine::error_callback(int error, const char* description)
	{
		CLogger("CGameEngine")->log(ELoggingLevel::SEVERE, "GLFW Error {0:X8} : {1}", error, description);
	}

	void CGameEngine::monitor_callback(GLFWmonitor* monitor, int status)
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

	CGameEngine::CGameEngine()
	{
		glfwSetErrorCallback(error_callback);

		if(!glfwInit())
			throw std::runtime_error{"GLFW initialization failure"};

		glfwSetMonitorCallback(monitor_callback);

		//get all monitors into our map
		int count = 0;
		GLFWmonitor** pmon = glfwGetMonitors(&count);
		while(count--)
			m_monitors.emplace(pmon[count], pmon[count]);
	}

	CGameEngine::~CGameEngine()
	{
		glfwTerminate();
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	util::Array<IMonitor*> CGameEngine::getAllMonitors() noexcept try
	{
		util::Array<IMonitor*> pmon{m_monitors.size()};
		std::transform(m_monitors.begin(), m_monitors.end(), pmon.begin(), [](auto& p){return &p.second;});
		return pmon;
	}
	catch(std::exception& e)
	{
		CLogger("CGameEngine")->log(ELoggingLevel::SEVERE, "{0}() : {1}", __func__, e.what());
		return {};
	}

	IMonitor* CGameEngine::getPrimaryMonitor() noexcept
	{
		GLFWmonitor* pmon = glfwGetPrimaryMonitor();
		if(pmon && m_monitors.count(pmon))
			return &m_monitors.at(pmon);
		else
			return nullptr;
	}

	IView* CGameEngine::createView() noexcept
	{
		//TODO finish
		return nullptr;
	}
}

R3VAPI r3dVoxel::IGameEngine* r3vInitialize() noexcept try
{
	static r3dVoxel::CGameEngine instance;
	return &instance;
}
catch(std::exception& e)
{
	r3dVoxel::CLogger(__func__).log(r3dVoxel::ELoggingLevel::SEVERE, e.what());
	return nullptr;
}
