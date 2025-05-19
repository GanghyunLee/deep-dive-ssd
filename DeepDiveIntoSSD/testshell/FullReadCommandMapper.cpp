#include "FullReadCommandMapper.h"

bool FullReadCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "fullread";
}

std::shared_ptr<ICommand> FullReadCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	return _fullReadCommandFactory();
}
