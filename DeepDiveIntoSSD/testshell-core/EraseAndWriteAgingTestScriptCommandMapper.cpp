#include "EraseAndWriteAgingTestScriptCommandMapper.h"
#include "EraseAndWriteAgingTestScriptCommand.h"

bool EraseAndWriteAgingTestScriptCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "4_eraseandwriteaging" ||
		userInputCommand[0] == "4_";
}

std::shared_ptr<ICommand> EraseAndWriteAgingTestScriptCommandMapper::GenerateCommand(
	const std::vector<std::string>& userInputCommand)
{
	return std::make_shared<EraseAndWriteAgingTestScriptCommand>(_scriptService);
}