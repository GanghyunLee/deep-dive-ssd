#pragma once
#include <functional>

#include "ICommandMapper.h"
#include "WriteReadAgingTestScriptService.h"

class WriteReadAgingTestScriptCommandMapper : public ICommandMapper
{
public:
	WriteReadAgingTestScriptCommandMapper(
		const std::shared_ptr<WriteReadAgingTestScriptService>& scriptService) :
		_scriptService(scriptService) {
	}

	~WriteReadAgingTestScriptCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	std::shared_ptr<WriteReadAgingTestScriptService> _scriptService;
};
