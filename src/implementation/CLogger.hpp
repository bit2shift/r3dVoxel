#pragma once

/*
 * ILogger implementation
 */
class CLogger : public r3dVoxel::ILogger
{
	std::string m_name;
	std::ofstream* m_file;

public:
	auto init(std::string name, std::ofstream& file) -> decltype(this)
	{
		m_name = name;
		m_file = &file;
		return this;
	}

	///////////////////////////
	//// Interface methods ////
	///////////////////////////

	void log(r3dVoxel::ELoggingLevel::Enum lvl, const char* str)
	{
		std::ostringstream buffer;

		std::time_t now = std::time(nullptr);
		buffer
			<< std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S ")
			<< '[' << lvl.name() << ']' << ' '
			<< '[' << m_name << ']' << ' '
			<< str << std::endl;

		std::clog << buffer.str();
		(*m_file) << buffer.str();
	}
};

R3VAPI r3dVoxel::ILogger* r3vGetLogger(const char* name, const char* fname)
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
