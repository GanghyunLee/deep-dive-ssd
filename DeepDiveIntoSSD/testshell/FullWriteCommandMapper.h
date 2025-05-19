#pragma once
#include <functional>

#include "FullWriteCommand.h"
#include "ICommandMapper.h"
#include "WriteCommand.h"

using FullWriteCommandFactory = std::function<std::shared_ptr<FullWriteCommand>(unsigned int)>;

class FullWriteCommandMapper : public ICommandMapper
{
public:
	FullWriteCommandMapper(const FullWriteCommandFactory& fullWriteCommandFactory) : _fullWriteCommandFactory(fullWriteCommandFactory) {}
	~FullWriteCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	FullWriteCommandFactory _fullWriteCommandFactory;
};
