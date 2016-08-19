#pragma once

#include <r3dVoxel/ILogger.hpp>

#include <iosfwd>
#include <string>

namespace r3dVoxel
{
	/*
	 * ILogger implementer
	 */
	class CLogger : public ILogger
	{
		static std::ofstream m_logfile;
		std::string m_name;

	public:
		auto operator()(std::string name) -> decltype(this);

		///////////////////////////
		//// Interface methods ////
		///////////////////////////

		void log(ELoggingLevel::type lvl, const char* str) noexcept;
	};
}
