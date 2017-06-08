#pragma once

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
		 * Usage: embedded (no gap hazards, I hope)
		 */
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
			~type_name()
			{
				std::free(m_name);
			}

			friend void swap(type_name& a, type_name& b) noexcept
			{
				auto tmp = a.m_name;
				a.m_name = b.m_name;
				b.m_name = tmp;
			}

			type_name(type_name&& tn) noexcept : m_name(nullptr)
			{
				swap(*this, tn);
			}

			type_name& operator=(type_name&& tn) noexcept
			{
				swap(*this, tn);
				return *this;
			}

			operator const char*() const noexcept
			{
				return m_name;
			}

			template<typename>
			friend type_name type_name();

			template<typename V>
			friend type_name type_name(V&&);
		};

		template<typename T>
		class type_name type_name()
		{
			return typeid(T);
		}

		template<typename V>
		class type_name type_name(V&& v)
		{
			return typeid(v);
		}
	}
}
