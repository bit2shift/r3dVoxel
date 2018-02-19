#pragma once

#include <cstdio>
#include <utility>

namespace r3dVoxel::memory
{
	class StaticLogger
	{
		const char* m_name;

	public:
		constexpr StaticLogger(const char* name) noexcept : m_name{name} {}

		template<typename... T>
		void operator()(const char* fmt, T&&... args) const noexcept
		{
			if(auto file = std::fopen(m_name, "a"))
			{
				std::fprintf(file, fmt, std::forward<T>(args)...);
				std::fclose(file);
			}
		}
	};
}
