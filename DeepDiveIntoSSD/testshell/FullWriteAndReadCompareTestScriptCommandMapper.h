#pragma once
#include <functional>

#include "FullWriteAndReadCompareTestScriptService.h"
#include "ICommandMapper.h"

class FullWriteAndReadCompareTestScriptCommandMapper : public ICommandMapper
{
public:
	FullWriteAndReadCompareTestScriptCommandMapper(
		const std::shared_ptr<FullWriteAndReadCompareTestScriptService>& scriptService) :
		_scriptService(scriptService) { }

	~FullWriteAndReadCompareTestScriptCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	std::shared_ptr<FullWriteAndReadCompareTestScriptService> _scriptService;
};

