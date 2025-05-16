#include "TestShellApplication.h"
#include <exception>
#include <iostream>
#include <string>

#include "ICommand.h"
#include "ICommandMapper.h"
#include "IView.h"

bool TestShellApplication::Run()
{
	while (true)
	{
		try
		{
			// 1. Get User Input
			std::vector<std::string> userInputCommand = GetUserInput();

			// 2. Parse Command
			for (auto& commandMapper : _ioc.GetCommandMappers())
			{
				if (false == commandMapper->IsSupport(userInputCommand))
					continue;

				// 3. Generate Command
				ICommand* command = commandMapper->GenerateCommand(userInputCommand);
				if (command == nullptr)
					throw std::exception("UNKNOWN ERROR!");

				// 4. Execute Command
				IView* view = command->Execute();

				// 5. Print Result
				if (view)
					view->Render(_oStream);
				
				return true;
			}

			// Failed to map command
			throw std::exception{ "INVALID COMMAND!" };
			return false;
		}
		catch (std::exception& ex)
		{
			_oStream << ex.what() << std::endl;
			return false;
		}
		return false;
	}
}

std::vector<std::string> TestShellApplication::GetUserInput()
{
	std::string userInput;
	_oStream << STR_SHELL_START << " ";
	std::getline(_iStream, userInput);
}
