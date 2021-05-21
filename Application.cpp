#pragma once

#include "Application.h"



void Application::registerCommand(std::unique_ptr<Command> command)
{
	AllCommand.insert(std::pair<std::string, std::unique_ptr<Command>>(command.get()->getName(), std::move(command)));

}

int Application::execute(int argc, char * argv[])
{
	std::map<std::string, std::unique_ptr<Command>>::iterator it;
	
	
	/*if (!std::strcmp(argv[1], "Cube")) {
		myCommand.insert(std::pair<std::string, std::string>(argv[2], argv[4]));
		myCommand.insert(std::pair<std::string, std::string>(argv[5], argv[7]));
		myCommand.insert(std::pair<std::string, std::string>(argv[8], argv[10]));
	}

	for (std::map <std::string, std::string>::const_iterator it = myCommand.begin();
		it != myCommand.end(); ++it)
	{
		
		std::cout << it->first << " " << it->second<<"\n";
	}
	
	if (!std::strcmp(argv[1], "Sphere")){}
	if (!std::strcmp(argv[1], "Spline")) {}
	//it = AllCommand.find(argv[1]);
	*/

	it = AllCommand.find("Sphere");

	it->second.get()->execute(myCommand);
	
	
			return 0;
}


