#pragma once
#include <memory>
#include <string>
#include <vector>
class ICommand;

class ICommandMapper
{
public:
	virtual ~ICommandMapper() = default;

public:
	virtual bool IsSupport(const std::vector<std::string>& userInputCommand) = 0;
	virtual std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) = 0;
};

