#pragma once

#include <cstdlib>
#include <cxxabi.h>
#include <new>
#include <stdexcept>
#include <typeinfo>
#include <utility>

namespace r3dVoxel
{
	namespace util
	{
		/*
		 * Obtains the fully qualified name of a type.
		 * Usage: embedded (no gap hazards, I hope)
		 */
		template<typename T = void>
		class type_name final
		{
			char* m_name;

			type_name(const std::type_info& ti)
			{
				int status = 0;
				m_name = abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status);
				switch(status)
				{
				case -1: throw std::bad_alloc();
				case -2: throw std::invalid_argument("mangled name");
				case -3: throw std::invalid_argument("unknown");
				}
			}

		public:
			template<typename V>
			type_name(V&& value) : type_name(typeid(value)) {}
			type_name() : type_name(typeid(T)) {}

			~type_name()
			{
				std::free(m_name);
			}

			operator const char*() noexcept
			{
				return m_name;
			}

			type_name(type_name&& other) noexcept
			{
				std::swap(m_name, other.m_name);
			}

			type_name& operator=(type_name&& other) noexcept
			{
				std::swap(m_name, other.m_name);
				return *this;
			}

			type_name(const type_name&) = delete;
			type_name& operator=(const type_name&) = delete;
		};
	}
}
