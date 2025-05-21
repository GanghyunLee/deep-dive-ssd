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
				view->Render(_logger);
		}
		catch (std::exception& ex)
		{
			_logger->print("TestShellApplication", __FUNCTION__, ex.what());
		}

		_logger->printLine();
	}

	return true;
}

std::string TestShellApplication::GetUserInputLowerStr()
{
	std::string userInput;
	if (_printShellPromptPrefix)
	{
		_logger->print("TestShellApplication", __FUNCTION__, STR_SHELL_START + " ", false);
	}
	std::getline(_iStream, userInput);

	return ParsingUtil::ToLowerString(userInput);
}
