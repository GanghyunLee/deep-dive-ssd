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
