#pragma once

#include "is_same_template.hpp"

#include <cstdlib>
#include <cxxabi.h>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

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
			template<typename V, typename = std::enable_if_t<!is_same_template<std::decay_t<V>, type_name>>>
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

			type_name(type_name&&) = delete;
			type_name(const type_name&) = delete;

			type_name& operator=(type_name&&) = delete;
			type_name& operator=(const type_name&) = delete;
		};
	}
}
