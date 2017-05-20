#include "CLogger.hpp"

#include <r3dVoxel/ILogger.hpp>
#include <r3dVoxel/r3vABI.hpp>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>

namespace r3dVoxel
{
	std::ofstream CLogger::m_logfile("r3dVoxel.log", std::ios_base::app);

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	void CLogger::log(ELoggingLevel::type lvl, const char* str) const noexcept
	{
		std::stringstream buffer;
		std::time_t now = std::time(nullptr);
		buffer
			<< std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S [")
			<< &lvl << "] ["
			<< m_name << "] "
			<< str << std::endl;

		std::clog << buffer.rdbuf();
		buffer.seekg(0);
		m_logfile << buffer.rdbuf();
	}
}

R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name) noexcept
{
	static std::map<std::string, r3dVoxel::CLogger> loggers;

	if(!name)
		name = "GLOBAL";

	return &loggers.emplace(name, name).first->second;
}
