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
			// 1. Find Matching Command
			std::shared_ptr<ICommand> command = FindMatchingCommand(userInput);

			// 2. Check if Failed to map command
			if (command == nullptr)
				throw std::exception{ "INVALID COMMAND" };

			// 3. Execute Command
			std::shared_ptr<IView> view = command->Execute();

			// 4. Print Result
			if (view)
				view->Render(_oStream);
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
