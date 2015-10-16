#include "StaticLogger.hpp"

namespace r3dVoxel
{
	namespace memory
	{
		StaticLogger::StaticLogger(const char* name) noexcept : m_file(std::fopen(name, "a"))
		{
			if(!m_file)
				m_file = stderr;
		}

		StaticLogger::~StaticLogger()
		{
			std::fclose(m_file);
		}
	}
}
