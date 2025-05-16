#pragma once
#include <string>
#include <vector>
class ICommand;

class ICommandMapper
{
public:
	virtual ~ICommandMapper() = default;

public:
	virtual bool IsSupport(const std::vector<std::string>& userInputCommand) = 0;
	virtual ICommand* GenerateCommand(const std::vector<std::string>& userInputCommand) = 0;
};

