#include "WriteCommandMapper.h"

#include "ParsingUtil.h"
#include "WriteCommand.h"

bool WriteCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 3)
		return false;

	return userInputCommand[0] == "write";
}

std::shared_ptr<ICommand> WriteCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	int lba = std::stoi(userInputCommand[1]);
	if (false == ParsingUtil::ContainsHexPrefix(userInputCommand[2]))
		throw std::exception{ "INVALID ARGUMENT" };

	unsigned int data = ParsingUtil::HexStringToDecimal(userInputCommand[2]);
	return _writeCommandFactory(lba, data);
}
