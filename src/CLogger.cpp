#include "CLogger.hpp"

#include <r3dVoxel/r3vABI.hpp>
#include <r3dVoxel/bugfix/put_time.hpp>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

namespace r3dVoxel
{
	auto CLogger::operator()(std::string name) -> decltype(this)
	{
		m_name = name;
		return this;
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	void CLogger::log(ELoggingLevel::type lvl, const char* str) noexcept
	{
		std::ostringstream buffer;
		std::time_t now = std::time(nullptr);
		buffer
			<< std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S [")
			<< &lvl << "] ["
			<< m_name << "] "
			<< str << std::endl;

		std::clog << buffer.str();
		m_logfile << buffer.str();
	}

	std::ofstream CLogger::m_logfile("r3dVoxel.log", std::ios_base::app);
}

R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name)
{
	static std::map<std::string, r3dVoxel::CLogger> loggers;

	if(!name)
		name = "GLOBAL";

	return loggers[name](name);
}
