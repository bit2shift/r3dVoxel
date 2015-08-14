#pragma once

#include "CMonitor.hpp"

#include <r3dVoxel/IGameEngine.hpp>
#include <map>

namespace r3dVoxel
{
	class IMonitor;
	class IView;

	/*
	 * IGameEngine implementer
	 */
	class CGameEngine : public IGameEngine
	{
		std::map<GLFWmonitor*, CMonitor> m_monitors;

		static void error_callback(int error, const char* description);
		static void monitor_callback(GLFWmonitor* monitor, int status);

	public:
		CGameEngine();
		~CGameEngine();

		///////////////////////////
		//// Interface methods ////
		///////////////////////////

		util::Array<IMonitor*> getAllMonitors() noexcept;
		IMonitor* getPrimaryMonitor() noexcept;
		IView* createView() noexcept;
	};
}
