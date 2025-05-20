#include "EraseRangeCommandMapper.h"

#include "ParsingUtil.h"

bool EraseRangeCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 3)
		return false;

	return userInputCommand[0] == "erase_range";
}

std::shared_ptr<ICommand> EraseRangeCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	try
	{
		int startLba = ParsingUtil::ConvertStringToOnlyPlusIntegerOrElseThrow(userInputCommand[1], true);
		int endLba = ParsingUtil::ConvertStringToOnlyPlusIntegerOrElseThrow(userInputCommand[2], true);

		ValidateLbaParameters(startLba, endLba);

		return _eraseCommandFactory(startLba, (endLba - startLba + 1));
	}
	catch (...)
	{
		throw std::exception{ "INVALID ARGUMENT" };
	}
}

void EraseRangeCommandMapper::ValidateLbaParameters(int startLba, int endLba)
{
	if (startLba > endLba)
		throw std::exception{ "Start LBA is greater than End LBA" };

}
