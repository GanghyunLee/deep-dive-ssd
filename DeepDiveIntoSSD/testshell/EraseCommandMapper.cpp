#include "EraseCommandMapper.h"

#include "ParsingUtil.h"

bool EraseCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 3)
		return false;

	return userInputCommand[0] == "erase";
}

std::shared_ptr<ICommand> EraseCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	try
	{
		int lba = ParsingUtil::ConvertStringToOnlyPlusIntegerOrElseThrow(userInputCommand[1], true);
		int size = ParsingUtil::ConvertStringToOnlyPlusIntegerOrElseThrow(userInputCommand[2], true);

		return _eraseCommandFactory(lba, size);
	}
	catch (...)
	{
		throw std::exception{ "INVALID ARGUMENT" };
	}
}