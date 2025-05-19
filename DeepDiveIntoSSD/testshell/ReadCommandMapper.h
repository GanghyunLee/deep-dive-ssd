#pragma once
#include <functional>

#include "ICommandMapper.h"
#include "ReadCommand.h"

using ReadCommandFactory = std::function<std::shared_ptr<ReadCommand>(int)>;


class ReadCommandMapper : public ICommandMapper
{
public:
	ReadCommandMapper(const ReadCommandFactory& readCommandFactory) : _readCommandFactory(readCommandFactory) {}
	~ReadCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	ReadCommandFactory _readCommandFactory;
};
