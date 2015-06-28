/*
 * Handy all-purpose logger
 */
class ILogger : public r3dVoxel::IClass
{
public:
	enum struct Level : std::uint8_t
	{
		OFF,
		SEVERE,
		WARNING,
		INFO,
		DEBUG,
		ALL
	};

	virtual void log(Level lvl, const char* str) = 0;

	template<typename... T>
	void log(Level lvl, const char* str, T&&... args)
	{
		static const std::regex re(R"re(\{(\d)(?:,([-+]?\d\d?))?(?::([A-Za-z])(\d\d?)?)?\}|[^])re");
		std::cregex_iterator begin(str, str + std::strlen(str), re);
		std::cregex_iterator end;
		std::ostringstream stream;
		while(begin != end)
		{
			std::cmatch cm = *begin++;
			if(cm[1].matched)
			{
				auto print = [&stream, &cm](const auto& t)
				{
					std::int32_t align = (cm[2].matched ? std::stoi(cm[2]) : 0);
					std::int8_t format = (cm[3].matched ? cm[3].str()[0] : 0);
					std::int32_t width = (cm[4].matched ? std::stoi(cm[4]) : 0);

					std::ostringstream field;
					switch(format)
					{
					case 'X':
					case 'x':
						field << std::hex << std::setw(width + 2);
						break;

					case 'O':
					case 'o':
						field << std::oct << std::setw(width + 1);
						break;

					//TODO more format specifiers
					}
					field << std::internal << std::setfill('0') << std::showbase << t;
					stream << std::setw(std::abs(align)) << (std::signbit(align) ? std::left : std::right) << field.str();
				};
				r3dVoxel::parameter_pack::at(std::stoi(cm[1]), print, std::forward<T>(args)...);
			}
			else
				stream << cm.str();
		}
		this->log(lvl, stream.str().c_str());
	}
};
