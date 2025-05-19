#pragma once
#include <memory>
#include "HelpCommand.h"
#include "ICommandMapper.h"

class HelpCommandMapper : public ICommandMapper
{
public:
	HelpCommandMapper(std::shared_ptr<HelpCommand> helpCommand) : _helpCommand(helpCommand) { }
	~HelpCommandMapper() override = default;

public:
	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override { return _helpCommand; }

private:
	std::shared_ptr<HelpCommand> _helpCommand;
};

