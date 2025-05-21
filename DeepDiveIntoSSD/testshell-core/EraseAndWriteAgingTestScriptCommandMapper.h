#pragma once
#include "EraseAndWriteAgingTestScriptService.h"
#include "ICommandMapper.h"

class EraseAndWriteAgingTestScriptCommandMapper : public ICommandMapper
{
public:
	EraseAndWriteAgingTestScriptCommandMapper(
		const std::shared_ptr<EraseAndWriteAgingTestScriptService>& scriptService) :
		_scriptService(scriptService) {
	}

	~EraseAndWriteAgingTestScriptCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	std::shared_ptr<EraseAndWriteAgingTestScriptService> _scriptService;
};
