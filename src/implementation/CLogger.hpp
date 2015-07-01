/*
 * ILogger implementation
 */
class CLogger : public r3dVoxel::ILogger
{
	auto init(std::string name) -> decltype(this)
	{
		//TODO ...
		return this;
	}

public:
	friend r3dVoxel::ILogger* r3vGetLogger(const char* name)
	{
		static std::map<std::string, CLogger> loggers;
		return loggers[name].init(name);
	}

	void log(Level lvl, const char* str)
	{
		//TODO
	}
};
