#include "CLogger.hpp"

#include <r3dVoxel/ILogger.hpp>
#include <r3dVoxel/r3vABI.hpp>
#include <r3dVoxel/util/spin_lock.hpp>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <mutex>
#include <new>
#include <ostream>
#include <sstream>
#include <string>

namespace r3dVoxel
{
	util::spin_lock CLogger::m_ttylock, CLogger::m_filelock;
	std::ofstream CLogger::m_logfile{"r3dVoxel.log", std::ios_base::app};

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	void CLogger::log(ELoggingLevel lvl, const char* str) const noexcept
	{
		std::stringstream buffer;
		std::time_t now = std::time(nullptr);
		buffer
			<< std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S [")
			<< &lvl << "] ["
			<< m_name << "] "
			<< str << std::endl;

		std::lock_guard{m_ttylock}, std::clog << buffer.rdbuf();
		buffer.seekg(0);
		std::lock_guard{m_filelock}, m_logfile << buffer.rdbuf();
	}
}

R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name) noexcept
{
	static r3dVoxel::util::spin_lock lock;
	static std::map<std::string, r3dVoxel::CLogger> loggers;

	if(!name)
		name = "GLOBAL";

	std::lock_guard guard{lock};
	if(auto [iter, added] = loggers.try_emplace(name, nullptr); added)
		return iter->second.~CLogger(), new(&iter->second) r3dVoxel::CLogger{iter->first.c_str()};
	else
		return &iter->second;
}
