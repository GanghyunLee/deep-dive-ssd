#include "TestShellApplication.h"
#include <sstream>
#include <string>
#include "ParsingUtil.h"

bool TestShellApplication::Run(int argc, char* argv[])
{
	// 1. Get User Input
	std::string userInput;

	while ((EXIT_STRING) != (userInput = GetUserInputLowerStr()))
	{
		try
		{
			InterpretUserCommandAndExecute(userInput);
		}
		catch (std::exception& ex)
		{
			_oStream << ex.what();
		}
		_oStream << std::endl;
	}

	return true;
}

std::string TestShellApplication::GetUserInputLowerStr()
{
	std::string userInput;
	if (_printShellPromptPrefix)
		_oStream << STR_SHELL_START << " ";
	std::getline(_iStream, userInput);

	return ParsingUtil::ToLowerString(userInput);
}
