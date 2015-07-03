/*
 * ILogger implementation
 */
class CLogger : public r3dVoxel::ILogger
{
	std::string m_name;
	std::ofstream* m_file;

	auto init(std::string name, std::ofstream& file) -> decltype(this)
	{
		m_name = name;
		m_file = &file;
		return this;
	}

public:
	friend r3dVoxel::ILogger* r3vGetLogger(const char* name, const char* fname)
	{
		typedef std::map<std::string, CLogger>       map_logger;
		typedef std::map<std::string, std::ofstream> map_file;

		static std::pair<map_logger, map_file> storage;

		if(!name)
			name = "r3dVoxel";

		if(!fname)
			fname = "r3dVoxel.log";

		auto& logger = storage.first[name];
		auto& file = storage.second[fname];

		if(!file.is_open())
			file.open(fname, std::ios_base::app);

		return logger.init(name, file);
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	void log(Level lvl, const char* str)
	{
		//TODO
	}
};
