#pragma once
#include "AbstractTestScriptService.h"
#include "ICommand.h"

struct ScriptCommandResult
{
	bool result;
};

class AbstractScriptCommand : public ICommand
{
public:
	AbstractScriptCommand(const std::shared_ptr<AbstractTestScriptService>& ssdScriptService) : _ssdScriptService(ssdScriptService) { }
	~AbstractScriptCommand() override = default;

	std::shared_ptr<IView> Execute() final;
	virtual std::string GetCommandName() = 0;
	bool GetScriptCommandResult() const { return _scriptCommandResult; }

protected:
	virtual std::shared_ptr<IView> GetView() = 0;

protected:
	std::shared_ptr<AbstractTestScriptService> _ssdScriptService;
	bool _scriptCommandResult{};
};

