#include "FullWriteCommandMapper.h"

#include "ParsingUtil.h"

bool FullWriteCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 2)
		return false;

	return userInputCommand[0] == "fullwrite";
}

std::shared_ptr<ICommand> FullWriteCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	if (false == ParsingUtil::ContainsHexPrefix(userInputCommand[1]))
		throw std::exception{ "INVALID ARGUMENT" };

	unsigned int data = ParsingUtil::HexStringToDecimal(userInputCommand[1]);
	return _fullWriteCommandFactory(data);
}
