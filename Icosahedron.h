#pragma once
#include "Command.h"
#include "Parser.h"


class Icosahedron : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string nameIcos = "Icosahedron";
};

