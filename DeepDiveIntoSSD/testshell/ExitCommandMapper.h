#pragma once
#include "ICommandMapper.h"

class ExitCommandMapper : public ICommandMapper
{
public:
	~ExitCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	ICommand* GenerateCommand(const std::vector<std::string>& userInputCommand) override;
};

