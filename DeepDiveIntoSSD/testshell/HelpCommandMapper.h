#pragma once
#include "HelpCommand.h"
#include "ICommandMapper.h"

class HelpCommandMapper : public ICommandMapper
{
public:
	HelpCommandMapper(HelpCommand* helpCommand) : _helpCommand(helpCommand) { }
	~HelpCommandMapper() override = default;

public:
	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	ICommand* GenerateCommand(const std::vector<std::string>& userInputCommand) override { return _helpCommand; }

private:
	HelpCommand* _helpCommand;
};

