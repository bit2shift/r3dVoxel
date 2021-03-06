#pragma once

#include <r3dVoxel/ILogger.hpp>
#include <r3dVoxel/util/spin_lock.hpp>

#include <iosfwd>

namespace r3dVoxel
{
	/*
	 * ILogger implementer
	 */
	class CLogger : public ILogger
	{
		static util::spin_lock m_ttylock, m_filelock;
		static std::ofstream m_logfile;
		const char* m_name;

	public:
		CLogger(const char* name) noexcept : m_name{name} {}

		ILogger* operator->() noexcept
		{
			return this;
		}

		///////////////////////////
		//// Interface methods ////
		///////////////////////////

		void log(ELoggingLevel lvl, const char* str) const noexcept;
	};
}
