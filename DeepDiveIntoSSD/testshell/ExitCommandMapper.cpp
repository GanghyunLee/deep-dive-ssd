#include "ExitCommandMapper.h"
#include "ExitCommand.h"

bool ExitCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() == 1)
		return userInputCommand[0] == "exit";

	return false;
}

ICommand* ExitCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	return new ExitCommand();
}
