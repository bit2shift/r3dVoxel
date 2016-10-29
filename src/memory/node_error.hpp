#pragma once

#include <cstdio>
#include <new>
#include <utility>

namespace r3dVoxel
{
	namespace memory
	{
		class node_error : public std::bad_alloc
		{
			char buffer[128];

		public:
			template<typename... T>
			node_error(const char* fmt, T&&... args) noexcept
			{
				std::snprintf(buffer, sizeof(buffer), fmt, std::forward<T>(args)...);
			}

			const char* what() const noexcept
			{
				return buffer;
			}
		};
	}
}
