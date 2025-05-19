#include "PartialLBAWriteTestScriptCommandMapper.h"
#include "PartialLBAWriteTestScriptCommand.h"

bool PartialLBAWriteTestScriptCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "2_partiallbawrite" ||
		userInputCommand[0] == "2_";
}

std::shared_ptr<ICommand> PartialLBAWriteTestScriptCommandMapper::GenerateCommand(
	const std::vector<std::string>& userInputCommand)
{
	return std::make_shared<PartialLBAWriteTestScriptCommand>(_scriptService);
}
