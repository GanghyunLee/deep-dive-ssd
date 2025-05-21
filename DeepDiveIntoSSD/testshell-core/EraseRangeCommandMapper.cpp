#include "EraseRangeCommandMapper.h"

#include "Constants.h"
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

		ConvertToValidLbaRange(startLba, endLba);

		return _eraseRangeCommandFactory(startLba, endLba);
	}
	catch (...)
	{
		throw std::exception{ "INVALID ARGUMENT" };
	}
}

void EraseRangeCommandMapper::ConvertToValidLbaRange(int& startLba, int& endLba)
{
	// startLba가 음수이면 보정
	if (startLba < 0) startLba = 0;

	// endLba가 음수이면 보정
	if (endLba < 0) endLba = 0;

	// endLba가 MaxLBA를 넘어가면 보정
	if (endLba > Constants::MAX_LBA)
		endLba = Constants::MAX_LBA;

	// startLba가 endLba보다 큰 경우 swap
	if (startLba > endLba)
		std::swap(startLba, endLba);
}
