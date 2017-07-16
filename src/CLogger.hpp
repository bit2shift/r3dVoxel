#pragma once

#include <r3dVoxel/ILogger.hpp>

#include <iosfwd>

namespace r3dVoxel
{
	/*
	 * ILogger implementer
	 */
	class CLogger : public ILogger
	{
		static std::ofstream m_logfile;
		const char* m_name;

	public:
		CLogger(const char* name) noexcept : m_name(name) {}

		static ILogger&& r3v(const char* name) noexcept
		{
			return static_cast<CLogger&&>(name);
		}

		///////////////////////////
		//// Interface methods ////
		///////////////////////////

		void log(ELoggingLevel::type lvl, const char* str) const noexcept;
	};
}
