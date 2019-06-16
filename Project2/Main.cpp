
#include "logger.h"

#include <iostream>

int main()
{
	std::string err_str;

	//Creates a handler to the logger
	logger* mylog = logger::Instance();

	//mode can be set between two modes
	//PRODUCTION_MODE: Relays everything to a txt file whose name is the current time of opening
	//DEBUG_MODE: Relays everything to the command prompt
	mylog->set_mode(PRODUCTION_MODE);

	//Used for when you want to start logging
	mylog->log_open();

	//logging a string
	err_str = "This is a test run";
	mylog->log(err_str);

	//logging a string
	err_str= "Entering for loop. ";
	mylog->log(err_str);


	for (int i = 0, j = 10; i < 10; i++, j--)
	{
		//logging a string
		err_str = "Entered for loop: counter : " + std::to_string(i);
		mylog->log(err_str);
		//logging astring
		err_str = "variable j = " + std::to_string(j);
		mylog->log(err_str);
	}
	
	//Used for closing the logger.
	mylog->log_close();

	//logs made after closing are thrown away
	err_str = "This will not be seen";
	mylog->log(err_str);


	//You can reopen if you want
	mylog->log_open();

	//printing to the txt file
	err_str = "This WILL be seen";
	mylog->log(err_str);

	//You can change the logging mode whenever you want
	mylog->set_mode(DEBUG_MODE);

	//This is sent to the command prompt
	err_str = "This will be output to the command prompt";
	mylog->log(err_str);

	mylog->set_mode(PRODUCTION_MODE);

	//This is sent back to the text file
	err_str = "This WILL be seen";
	mylog->log(err_str);

	mylog->log_close();



	return 0;

}