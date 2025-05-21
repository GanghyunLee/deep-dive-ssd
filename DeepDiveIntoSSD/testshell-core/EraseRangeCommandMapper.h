#pragma once
#include <functional>
#include "ICommandMapper.h"
#include "EraseRangeCommand.h"

using EraseRangeCommandFactory = std::function<std::shared_ptr<EraseRangeCommand>(int, int)>;

class EraseRangeCommandMapper : public ICommandMapper
{
public:
	EraseRangeCommandMapper(const EraseRangeCommandFactory& eraseRangeCommandFactory) : _eraseRangeCommandFactory(eraseRangeCommandFactory) {}
	~EraseRangeCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

	void ConvertToValidLbaRange(int& startLba, int& endLba);

protected:
	EraseRangeCommandFactory _eraseRangeCommandFactory;
};