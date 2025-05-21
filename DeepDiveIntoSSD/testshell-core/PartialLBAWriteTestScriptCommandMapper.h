#pragma once
#include <functional>
#include "ICommandMapper.h"
#include "PartialLbaWriteTestScriptService.h"

class PartialLBAWriteTestScriptCommandMapper : public ICommandMapper
{
public:
	PartialLBAWriteTestScriptCommandMapper(
		const std::shared_ptr<PartialLbaWriteTestScriptService>& scriptService) :
		_scriptService(scriptService) {
	}

	~PartialLBAWriteTestScriptCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	std::shared_ptr<PartialLbaWriteTestScriptService> _scriptService;
};

