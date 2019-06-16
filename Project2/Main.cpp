
#include "logger.h"

#include <iostream>

int main()
{
	std::string err_str;

	logger* mylog = logger::Instance();

	mylog->set_mode(PRODUCTION_MODE);
	mylog->log_open();

	mylog->log("This is a test run");

	mylog->log("Entering for loop.");
	for (int i = 0, j = 10; i < 10; i++, j--)
	{
		err_str = "Entered for loop: counter : " + std::to_string(i);
		mylog->log(err_str);
		err_str = "variable j = " + std::to_string(j);
		mylog->log(err_str);
	}

	mylog->log_close();
	return 0;

}