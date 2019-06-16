

#if _WIN64
#define _LOCALTIME(curtime,t) (localtime_s(&curtime, &t))
#else
#include <stddef.h>
#define _LOCALTIME(curtime,t) (curtime=*localtime(&t))
#endif

#ifndef LOGGER
#define LOGGER

#include <string>
#include <mutex>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <time.h>
#include <sstream>

#define STRINGHEADER "Logging Info: "

enum LoggerType { DEBUG_MODE, PRODUCTION_MODE };

const std::string LoggerName[2] = { "DEBUG_MODE", "PRODUCTION_MODE" };


class logger
{
private:

	LoggerType mode; //check enum
	std::string directory; //end point of our logs
	std::string filename;
	bool isopen;
	std::mutex mtx;
	std::ofstream mylogger;


	bool move();
	LoggerType get_LoggerType() { return this->mode; }

	// halted constructors
	logger()
	{
		//setting defaults

		std::string str = "./";
		set_directory(str);
		set_mode(PRODUCTION_MODE);

		mtx.lock(); //critical area


		//section gets time for file name
		time_t t = std::time(nullptr);
		tm curtime;
		_LOCALTIME(curtime,t);
		//setting name
		std::stringstream logstring;
		logstring << std::put_time(&curtime, "%Y_%m_%d_%H%M%S") << ".txt";
		this->filename = logstring.str();

		mtx.unlock(); //end of critical area
	}

	logger(logger const&) {};
	logger& operator=(logger const&) {};

	static logger* p_Instance;

public:
	static logger* Instance();
	~logger();
	bool log(char* sstr);
	bool log(std::string sstr);
	bool log(int number);
	bool log(float number);
	bool log_open();
	bool log_close();

	void set_directory(std::string DIR)
	{
		mtx.lock();
		this->directory = DIR;
		mtx.unlock();
	}
	void set_directory(char* DIR) { set_directory(static_cast<std::string>(DIR)); }
	void set_mode(LoggerType mode)
	{
		mtx.lock();
		this->mode = mode;
		mtx.unlock();
	}
	bool is_running() { return isopen; }
	std::string get_filename() { return this->filename; }
};




#endif