#include "WriteCommandMapper.h"

#include "WriteCommand.h"

bool WriteCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	return false;
}

std::shared_ptr<ICommand> WriteCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	// TODO
	int lba = 0;
	unsigned int data = 0;

	return _writeCommandFactory(lba, data);
}
