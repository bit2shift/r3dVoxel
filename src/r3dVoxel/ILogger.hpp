#pragma once

/*
 * Logging level
 */
namespace ELoggingLevel
{
	ENUM_TYPE(std::uint8_t)
	ENUM(OFF)
	ENUM(SEVERE)
	ENUM(WARNING)
	ENUM(INFO)
	ENUM(DEBUG)
	ENUM(ALL)
}

/*
 * Handy all-purpose logger
 */
class ILogger : public r3dVoxel::IClass
{
public:
	virtual void log(r3dVoxel::ELoggingLevel::Enum lvl, const char* str) = 0;

	template<typename... T>
	void log(r3dVoxel::ELoggingLevel::Enum lvl, const char* str, T&&... args)
	{
		static const std::regex re(R"re(\{(\d)(?:,(-?\d\d?))?(?::([A-Za-z])(\d\d?)?)?\}|[^])re");
		std::cregex_iterator begin(str, str + std::strlen(str), re);
		std::cregex_iterator end;
		std::ostringstream stream;
		while(begin != end)
		{
			std::cmatch cm = *begin++;
			if(cm[1].matched)
			{
				auto print = [&stream, &cm](auto t)
				{
					std::int32_t align = (cm[2].matched ? std::stoi(cm[2]) : 0);
					std::int8_t format = (cm[3].matched ? cm[3].str()[0] : 0);
					std::int32_t width = (cm[4].matched ? std::stoi(cm[4]) : 0);

					std::ostringstream field;
					field << std::internal << std::setfill('0');
					switch(format)
					{
					case 'X':
					case 'x': // hexadecimal notation
						field << "0x" << std::hex << std::uppercase << std::setw(width) << t;
						break;

					case 'O':
					case 'o': // octal notation
						field << '0' << std::oct << std::setw(width) << t;
						break;

					case 'H': // upper-case hexadecimal (no base)
						field << std::hex << std::uppercase << std::setw(width) << t;
						break;

					case 'h': // lower-case hexadecimal (no base)
						field << std::hex << std::nouppercase << std::setw(width) << t;
						break;

					case 'I':
					case 'i': // signed integer (forced specifier)
						field << typename std::conditional<std::is_integral<decltype(t)>::value, std::intmax_t, decltype(t)>::type(t);
						break;

					case 'U':
					case 'u': // unsigned integer (forced specifier)
						field << typename std::conditional<std::is_integral<decltype(t)>::value, std::uintmax_t, decltype(t)>::type(t);
						break;

					//TODO more format specifiers

					default:
						field << std::right << std::setfill(' ') << t;
						break;
					}
					stream << std::setw(std::abs(align)) << (std::signbit(align) ? std::left : std::right) << field.str();
				};
				r3dVoxel::parameter_pack::at(std::stoul(cm[1]), print, std::forward<T>(args)...);
			}
			else
				stream << cm.str();
		}
		this->log(lvl, stream.str().c_str());
	}
};
