#pragma once
#include <memory>
#include "FlushCommand.h"
#include "ICommandMapper.h"

class FlushCommandMapper : public ICommandMapper
{
public:
	FlushCommandMapper(std::shared_ptr<FlushCommand> flushCommand) : _flushCommand(flushCommand) {}
	~FlushCommandMapper() override = default;

public:
	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override { return _flushCommand; }

private:
	std::shared_ptr<FlushCommand> _flushCommand;
};

