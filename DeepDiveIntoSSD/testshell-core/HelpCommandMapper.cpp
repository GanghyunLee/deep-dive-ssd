#include "HelpCommandMapper.h"
#include "HelpCommand.h"

bool HelpCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "help";
}
