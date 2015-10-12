#include "StaticLogger.hpp"

#include <cerrno>
#include <system_error>

namespace r3dVoxel
{
	namespace memory
	{
		StaticLogger::StaticLogger(const char* name) : m_file(std::fopen(name, "a"))
		{
			if(!m_file)
				throw std::system_error(EIO, std::system_category());
		}

		StaticLogger::~StaticLogger()
		{
			std::fclose(m_file);
		}
	}
}
