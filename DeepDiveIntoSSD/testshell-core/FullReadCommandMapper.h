#pragma once
#include <functional>
#include "FullReadCommand.h"
#include "ICommandMapper.h"
#include "WriteCommand.h"

using FullReadCommandFactory = std::function<std::shared_ptr<FullReadCommand>()>;

class FullReadCommandMapper : public ICommandMapper
{
public:
	FullReadCommandMapper(const FullReadCommandFactory& fullReadCommandFactory) : _fullReadCommandFactory(fullReadCommandFactory) {}
	~FullReadCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	FullReadCommandFactory _fullReadCommandFactory;
};
