#pragma once

#include "IClass.hpp"
#include "util/Enum.hpp"
#include "util/parameter_pack.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <regex>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

namespace r3dVoxel
{
	/*
	 * Logging level
	 */
	namespace ELoggingLevel
	{
		ENUM_TYPE(std::uint8_t);
		#line 0
		ENUM(OFF);
		ENUM(SEVERE);
		ENUM(WARNING);
		ENUM(INFO);
		ENUM(DEBUG);
		ENUM(ALL);
		#line 34
	}

	/*
	 * Handy all-purpose logger
	 */
	class ILogger : public IClass
	{
		template<typename T>
		std::string print(std::string& format, T&& object)
		{
			int width = (format.length() > 1) ? std::stoi(format.substr(1)) : 0;

			std::ostringstream field;
			field << std::internal << std::setfill('0');
			switch(format[0])
			{
			case 'X':
			case 'x': //hexadecimal notation
				field << "0x" << std::hex << std::uppercase << std::setw(width) << object;
				break;

			case 'O':
			case 'o': //octal notation
				field << '0' << std::oct << std::setw(width) << object;
				break;

			case 'H': //upper-case hexadecimal (no base)
				field << std::hex << std::uppercase << std::setw(width) << object;
				break;

			case 'h': //lower-case hexadecimal (no base)
				field << std::hex << std::nouppercase << std::setw(width) << object;
				break;

			case 'I':
			case 'i': //signed integer (forced specifier)
				field << typename std::conditional<std::is_integral<T>::value, std::intmax_t, T>::type(object);
				break;

			case 'U':
			case 'u': //unsigned integer (forced specifier)
				field << typename std::conditional<std::is_integral<T>::value, std::uintmax_t, T>::type(object);
				break;

			case 'Z':
			case 'z': //std::size_t specifier, max hex digits (8 for 32-bit, 16 for 64-bit)
				field << "0x" << std::hex << std::uppercase << std::setw(sizeof(std::size_t) << 1);
				field << typename std::conditional<std::is_integral<T>::value, std::size_t, T>::type(object);
				break;

			//TODO more format specifiers

			default:
				field << std::right << std::setfill(' ') << object;
				break;
			}

			return field.str();
		}

	public:
		virtual void log(ELoggingLevel::type lvl, const char* str) noexcept = 0;

		template<typename... T>
		void log(ELoggingLevel::type lvl, const char* str, T&&... args)
		{
			static const int index[]{-1, 1, 2, 3};
			static const std::regex rex(R"(\{(\d)(,-?\d{1,2})?(:[[:alpha:]]\d{0,2})?\})", std::regex::optimize);
			std::cregex_token_iterator begin(str, str + std::char_traits<char>::length(str), rex, index), end;
			std::ostringstream stream;
			while(begin != end)
			{
				auto position = -1UL;
				std::string format{0};
				for(auto i : index)
				{
					if(begin == end)
						break;

					auto cm = *begin++;

					if(!cm.matched)
						continue;

					switch(i)
					{
					case -1:
						stream << cm;
						break;

					case 1:
						position = std::stoul(cm);
						break;

					case 2:
						{
							auto align = std::stoi(std::string(cm.first + 1, cm.second));
							stream << std::setw(std::abs(align)) << (std::signbit(align) ? std::left : std::right);
						}
						break;

					case 3:
						format.assign(cm.first + 1, cm.second);
						break;
					}
				}

				if(position < 10)
				{
					util::parameter_pack::at
					(
						position,
						[&stream, this, &format](auto object)
						{
							stream << this->print(format, std::forward<decltype(object)>(object));
						},
						std::forward<T>(args)...
					);
				}
			}

			this->log(lvl, stream.str().c_str());
		}
	};
}
