#include "ReadCommandMapper.h"

bool ReadCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 2)
		return false;

	return userInputCommand[0] == "read";
}

std::shared_ptr<ICommand> ReadCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	int lba = std::stoi(userInputCommand[1]);
	return _readCommandFactory(lba);
}
