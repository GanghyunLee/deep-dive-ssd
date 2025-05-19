#include "WriteReadAgingTestScriptCommandMapper.h"

#include "WriteReadAgingTestScriptCommand.h"

bool WriteReadAgingTestScriptCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "3_writereadaging" ||
		userInputCommand[0] == "3_";
}

std::shared_ptr<ICommand> WriteReadAgingTestScriptCommandMapper::GenerateCommand(
	const std::vector<std::string>& userInputCommand)
{
	return std::make_shared<WriteReadAgingTestScriptCommand>(_scriptService);
}
