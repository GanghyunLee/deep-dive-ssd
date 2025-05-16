#include "TestShellApplication.h"
#include <exception>
#include <iostream>
#include <sstream>
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
			ICommand* command = nullptr;
			for (auto& commandMapper : _ioc.GetCommandMappers())
			{
				if (false == commandMapper->IsSupport(userInputCommand))
					continue;

				command = commandMapper->GenerateCommand(userInputCommand);
			}

			// 3. Check if Failed to map command
			if (command == nullptr)
				throw std::exception{ "INVALID COMMAND" };

			// 4. Execute Command
			IView* view = command->Execute();

			// 5. Print Result
			if (view)
				view->Render(_oStream);

			// 6. Check If the command has quit command
			bool needToExit = command->NeedToExitAfterExecute();

			// 7. Delete Command
			if (command)
			{
				delete command;
				command = nullptr;
			}

			if (needToExit)
				break;
		}
		catch (std::exception& ex)
		{
			_oStream << ex.what() << std::endl;
		}
	}

	return true;
}

std::vector<std::string> TestShellApplication::GetUserInput()
{
	std::string userInput;
	_oStream << STR_SHELL_START << " ";
	std::getline(_iStream, userInput);

	std::vector<std::string> splitedUserInput;
	std::stringstream ss(userInput);  // 입력된 문자열을 stringstream으로 변환

	// 공백을 기준으로 단어들을 하나씩 읽어 vector에 넣기
	{
		std::string word;
		while (ss >> word) {
			splitedUserInput.push_back(word);
		}
	}
	return splitedUserInput;
}
