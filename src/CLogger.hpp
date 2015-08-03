#pragma once

#include <r3dVoxel/ILogger.hpp>
#include <fstream>

namespace r3dVoxel
{
	/*
	 * ILogger implementer
	 */
	class CLogger : public ILogger
	{
		std::string m_name;
		std::ofstream* m_file;

	public:
		auto init(std::string name, std::ofstream& file) -> decltype(this);

		///////////////////////////
		//// Interface methods ////
		///////////////////////////

		void log(ELoggingLevel::type lvl, const char* str) noexcept;
	};
}
