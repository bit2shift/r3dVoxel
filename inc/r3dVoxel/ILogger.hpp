#pragma once

#include "IClass.hpp"
#include "util/Enum.hpp"
#include "util/parameter_pack.hpp"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <regex>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <utility>

namespace r3dVoxel
{
	ENUM_TYPE(ELoggingLevel, std::uint8_t)
	{
		ENUM_VALUE(OFF);
		ENUM_VALUE(SEVERE);
		ENUM_VALUE(WARNING);
		ENUM_VALUE(INFO);
		ENUM_VALUE(DEBUG);
		ENUM_VALUE(ALL);
	};

	/*
	 * Handy all-purpose logger
	 */
	class ILogger : public IClass
	{
		static auto& regex() noexcept
		{
			static const std::regex rex(R"(\{(\d)(,-?\d{1,2})?(:[[:alpha:]]\d{0,2})?\})", std::regex::optimize);
			return rex;
		}

		template<typename N, typename I>
		static N number(I begin, I end)
		{
			N num{};
			bool neg = ((*begin == '-') && begin++);
			while(begin < end)
				num = (num * 10) + N(*begin++ - '0');
			return neg ? -num : num;
		}

		template<typename T>
		static auto print(char format, int width, T&& object)
		{
			std::stringstream field;
			field << std::internal << std::setfill('0');

			switch(format)
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
			case 'h': //lower-case hexadecimal (no base)
				field << std::hex << (std::isupper(format) ? std::uppercase : std::nouppercase) << std::setw(width) << object;
				break;

			case 'I':
			case 'i': //signed integer (forced specifier)
				field << std::conditional_t<std::is_integral_v<std::decay_t<T>>, std::intmax_t, T>(std::forward<T>(object));
				break;

			case 'U':
			case 'u': //unsigned integer (forced specifier)
				field << std::conditional_t<std::is_integral_v<std::decay_t<T>>, std::uintmax_t, T>(std::forward<T>(object));
				break;

			case 'Z':
			case 'z': //std::size_t specifier, max hex digits (8 for 32-bit, 16 for 64-bit)
				field << "0x" << std::hex << std::uppercase << std::setw(sizeof(std::size_t) << 1);
				field << std::conditional_t<std::is_integral_v<std::decay_t<T>>, std::size_t, T>(std::forward<T>(object));
				break;

			//TODO more format specifiers

			default:
				field << std::right << std::setfill(' ') << object;
				break;
			}

			return field;
		}

	public:
		virtual void log(ELoggingLevel lvl, const char* str) const noexcept = 0;

		/*
		 * =======================
		 * Composite Format String
		 * =======================
		 *
		 * Syntax:
		 *   {index[,alignment][:format]}
		 *
		 * Arguments:
		 * - index: single digit (range: [0, 9])
		 * - alignment: signed number (range: [-99, 99])
		 * - format: single letter followed by two digits at most (range: [0, 99])
		 *
		 * Note:
		 *   Elements inside the brackets are optional
		 *   and should appear in the specified order.
		 *
		 * Example:
		 *   logger->log(r3dVoxel::ELoggingLevel::INFO, "({1,-4}) ({0:X4})", 123, 69);
		 *   It will print "(69  ) (0x007B)" to the specified logger.
		 */
		template<typename... T>
		void log(ELoggingLevel lvl, std::string_view str, T&&... args) const
		{
			constexpr int index[]{-1, 1, 2, 3};
			std::cregex_token_iterator begin(str.begin(), str.end(), regex(), index), end;
			std::ostringstream stream;
			while(begin != end)
			{
				unsigned position = -1U;
				int alignment = 0;
				char format = 0;
				int width = 0;
				for(int i : index)
				{
					if(begin == end)
						break;

					auto cm = *begin++;

					if(!cm.matched)
						continue;

					switch(i)
					{
					case -1:
						stream.write(cm.first, cm.length());
						break;

					case 1:
						position = number<unsigned>(cm.first, cm.second);
						break;

					case 2:
						alignment = number<int>(cm.first + 1, cm.second);
						break;

					case 3:
						format = cm.first[1];
						width = number<int>(cm.first + 2, cm.second);
						break;
					}
				}

				if(position < 10)
				{
					util::parameter_pack::at
					(
						position,
						[&stream, alignment, format, width](auto&& object)
						{
							auto&& str = print(format, width, std::forward<decltype(object)>(object));

							if(alignment > 0)
								stream << std::setw(alignment - int(str.tellp())) << "";

							stream << str.rdbuf();

							if(alignment < 0)
								stream << std::setw(-alignment - int(str.tellp())) << "";
						},
						std::forward<T>(args)...
					);
				}
			}

			this->log(lvl, stream.str().c_str());
		}
	};
}
