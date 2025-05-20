#pragma once
#include <functional>
#include "ICommandMapper.h"
#include "EraseCommand.h"

class EraseRangeCommandMapper : public ICommandMapper
{
public:
	EraseRangeCommandMapper(const EraseCommandFactory& eraseCommandFactory) : _eraseCommandFactory(eraseCommandFactory) {}
	~EraseRangeCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

	void ValidateLbaParameters(int startLba, int endLba);

protected:
	EraseCommandFactory _eraseCommandFactory;
};