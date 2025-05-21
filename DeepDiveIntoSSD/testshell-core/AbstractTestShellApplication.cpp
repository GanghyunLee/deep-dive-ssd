#include "AbstractTestShellApplication.h"
#include <algorithm>
#include <exception>
#include <sstream>
#include <string>
#include "ICommand.h"
#include "ICommandMapper.h"
#include "IView.h"

std::shared_ptr<ICommand> AbstractTestShellApplication::FindMatchingCommand(const std::string& userInput)
{
	std::shared_ptr<ICommand> command = nullptr;

	// Split User Input Command String
	std::vector<std::string> userInputCommand = SplitUserInputCommand(userInput);

	// Parse Command
	for (auto& commandMapper : _commandMappers)
	{
		if (false == commandMapper->IsSupport(userInputCommand))
			continue;

		command = commandMapper->GenerateCommand(userInputCommand);
		break;
	}

	return command;
}

std::vector<std::string> AbstractTestShellApplication::SplitUserInputCommand(const std::string& input)
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
