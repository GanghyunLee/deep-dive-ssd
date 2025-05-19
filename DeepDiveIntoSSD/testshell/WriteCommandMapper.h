#pragma once
#include <functional>

#include "ICommandMapper.h"
#include "WriteCommand.h"

using WriteCommandFactory = std::function<std::shared_ptr<WriteCommand>(int, unsigned int)>;

class WriteCommandMapper : public ICommandMapper
{
public:
	WriteCommandMapper(const WriteCommandFactory& writeCommandFactory) : _writeCommandFactory(writeCommandFactory) {}
	~WriteCommandMapper() override = default;

	bool IsSupport(const std::vector<std::string>& userInputCommand) override;
	std::shared_ptr<ICommand> GenerateCommand(const std::vector<std::string>& userInputCommand) override;

protected:
	bool ContainsHexPrefix(const std::string& str);
	unsigned int HexStringToDecimal(const std::string& hexStr);

protected:
	WriteCommandFactory _writeCommandFactory;
};