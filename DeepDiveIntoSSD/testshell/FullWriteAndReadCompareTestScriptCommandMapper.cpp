#include "FullWriteAndReadCompareTestScriptCommandMapper.h"

#include "FullWriteAndReadCompareTestScriptCommand.h"

bool FullWriteAndReadCompareTestScriptCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "1_fullwriteandreadcompare" || 
		userInputCommand[0] == "1_";
}

std::shared_ptr<ICommand> FullWriteAndReadCompareTestScriptCommandMapper::GenerateCommand(
	const std::vector<std::string>& userInputCommand)
{
	return std::make_shared<FullWriteAndReadCompareTestScriptCommand>(_scriptService);
}
