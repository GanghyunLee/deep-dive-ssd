#include "TestShellApplication.h"

#include <algorithm>
#include <exception>
#include <sstream>
#include <string>
#include "ICommand.h"
#include "ICommandMapper.h"
#include "IView.h"

bool TestShellApplication::Run()
{
	// 1. Get User Input
	std::string userInput;
	while ((EXIT_STRING) != (userInput = GetUserInputLowerStr()))
	{
		try
		{
			// 2. Split User Input Command String
			std::vector<std::string> userInputCommand = SplitUserInputCommand(userInput);

			// 3. Parse Command
			ICommand* command = nullptr;
			for (auto& commandMapper : _commandMappers)
			{
				if (false == commandMapper->IsSupport(userInputCommand))
					continue;

				command = commandMapper->GenerateCommand(userInputCommand);
			}

			// 4. Check if Failed to map command
			if (command == nullptr)
				throw std::exception{ "INVALID COMMAND" };

			// 5. Execute Command
			IView* view = command->Execute();

			// 6. Print Result
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

	// 모든 문자를 소문자로 변환
	std::transform(userInput.begin(), userInput.end(), userInput.begin(), [](unsigned char c) {
		return std::tolower(c);
		});

	return userInput;
}

std::vector<std::string> TestShellApplication::SplitUserInputCommand(const std::string& input)
{
	std::stringstream ss(input);  // 입력된 문자열을 stringstream으로 변환

	// 공백을 기준으로 단어들을 하나씩 읽어 vector에 넣기
	std::vector<std::string> splitedUserInput;
	{
		std::string word;
		while (ss >> word) {
			splitedUserInput.push_back(word);
		}
	}
	return splitedUserInput;
}
