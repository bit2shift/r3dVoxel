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
		class type_name_t final
		{
			char* m_name;

		public:
			type_name_t(const std::type_info& ti)
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

			type_name_t(type_name_t&& tn) noexcept : m_name(nullptr)
			{
				std::swap(m_name, tn.m_name);
			}

			~type_name_t()
			{
				std::free(m_name);
			}

			type_name_t& operator=(type_name_t&& tn) noexcept
			{
				std::swap(m_name, tn.m_name);
				return *this;
			}

			operator const char*() noexcept
			{
				return m_name;
			}
		};

		template<typename T>
		type_name_t type_name()
		{
			return typeid(T);
		}

		template<typename V>
		type_name_t type_name(V&& v)
		{
			return typeid(v);
		}
	}
}
