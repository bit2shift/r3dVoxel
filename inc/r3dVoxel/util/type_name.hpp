#pragma once

#include <cstddef>
#include <cstdlib>
#include <cxxabi.h>
#include <new>
#include <stdexcept>
#include <typeinfo>

namespace r3dVoxel
{
	namespace util
	{
		/*
		 * Obtains the fully qualified name of a type.
		 * Usage: embedded (no gap hazards)
		 */
		template<typename T = std::nullptr_t>
		class type_name final
		{
			char* m_name;

		public:
			template<typename V = T>
			type_name(V&& value = {})
			{
				int status = 0;
				m_name = abi::__cxa_demangle(typeid(value).name(), nullptr, nullptr, &status);
				switch(status)
				{
				case -1: throw std::bad_alloc();
				case -2: throw std::invalid_argument("mangled name");
				case -3: throw std::invalid_argument("unknown");
				}
			}

			~type_name()
			{
				std::free(m_name);
			}

			operator char*() noexcept
			{
				return m_name;
			}
		};
	}
}
