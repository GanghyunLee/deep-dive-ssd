#include "EraseCommandMapper.h"
#include "Constants.h"
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
		int size = std::stoi(userInputCommand[2]);

		ConvertToValidLbaRange(lba, size);

		return _eraseCommandFactory(lba, size);
	}
	catch (...)
	{
		throw std::exception{ "INVALID ARGUMENT" };
	}
}

void EraseCommandMapper::ConvertToValidLbaRange(int& lba, int& size)
{
	// size에 대한 음수 처리
	if (size < 0)
	{
		int targetStartLba = lba + size + 1;

		if (targetStartLba < 0)
		{
			size -= targetStartLba;
			targetStartLba = 0;
		}

		lba = targetStartLba;
		size *= -1;
	}
}
