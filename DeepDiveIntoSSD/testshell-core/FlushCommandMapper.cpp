#include "FlushCommandMapper.h"

bool FlushCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 1)
		return false;

	return userInputCommand[0] == "flush";
}
