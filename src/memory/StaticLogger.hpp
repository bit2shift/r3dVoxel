#pragma once

#include <cstdio>
#include <utility>

namespace r3dVoxel
{
	namespace memory
	{
		class StaticLogger
		{
			std::FILE* m_file;

		public:
			StaticLogger(const char* name);
			~StaticLogger();

			template<typename... T>
			void operator()(const char* fmt, T&&... args) noexcept
			{
				std::fprintf(m_file, fmt, std::forward<T>(args)...);
			}
		};
	}
}
