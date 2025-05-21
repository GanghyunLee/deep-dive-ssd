#pragma once
#include <functional>

#include "ICommandMapper.h"
#include "EraseCommand.h"

class EraseCommandMapper : public ICommandMapper
{
public:
	EraseCommandMapper(const EraseCommandFactory& eraseCommandFactory) : _eraseCommandFactory(eraseCommandFactory) {}
	~EraseCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

	void ConvertToValidLbaRange(int& lba, int& size);

protected:
	EraseCommandFactory _eraseCommandFactory;
};