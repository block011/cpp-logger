#include "logger.h"

logger* logger::p_Instance = NULL;

logger* logger::Instance()
{
	if (!p_Instance)
	{
		p_Instance = new logger();
	}
	return p_Instance;
}


logger::~logger()
{
	if (this->is_running())
	{
		log_close();
	}

}

bool logger::log(char* sstr)
{
	return this->log(static_cast<std::string>(sstr)) ? true : false;
}

bool logger::log(std::string sstr)
{
	//dont log if not running
	if (!this->is_running())
	{
		return false;
	}

	//LOG
	if (this->get_LoggerType() == PRODUCTION_MODE)
	{
		mtx.lock();
		this->mylogger << STRINGHEADER << sstr << std::endl;
		mtx.unlock();
	}
	else
	{
		std::cout << STRINGHEADER << sstr << std::endl;
	}

	return true;
}

bool logger::log(int number)
{
	return this->log(std::to_string(number)) ? true : false;
}

bool logger::log(float number)
{
	return this->log(std::to_string(number)) ? true : false;
}

bool logger::log_open()
{
	try {
		if (!is_running())
		{
			isopen = true; //Currently logging
			//creating file handler
			mylogger.open(filename.c_str());
			if (get_LoggerType() == PRODUCTION_MODE)
			{
				std::string sstr;
				sstr = "Successfully opend log";
				log(sstr);
				sstr = "log values -------------";
				log(sstr);
				sstr = "File name = " + get_filename();
				log(sstr);
				sstr = "Logger Type = " + LoggerName[get_LoggerType()];
				log(sstr);
				sstr = "------------------------";
				log(sstr);
			}

		}
		return true;
	}
	catch (...)
	{
		std::cout << "Error has occured while opening file handler." << std::endl;
		return false;
	}

}

bool logger::log_close()
{

	try {
		if (is_running())
		{
			if (get_LoggerType() == PRODUCTION_MODE)
			{
				std::string sstr;
				sstr = "Attempting to close log";
				log(sstr);
				sstr = "log values -------------";
				log(sstr);

				sstr = "File name = " + get_filename();
				log(sstr);
				sstr = "Logger Type = " + LoggerName[get_LoggerType()];
				log(get_LoggerType());

				sstr = "------------------------";
				log(sstr);
			}
			move();
			isopen = false;
		}
		return true;
	}
	catch (...)
	{
		std::cout << "Error has occured while closing file handler." << std::endl;
		return false;
	}

}

bool logger::move()
{

	//TODO: Transfer file into new location

	mylogger.close();
	//checking if file was empty, then we just get rid of it
	std::ifstream file(filename.c_str());
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		file.close();
		std::remove(filename.c_str());
	}
	else //otherwise we move
	{
		file.close();
	}



	return true;
}