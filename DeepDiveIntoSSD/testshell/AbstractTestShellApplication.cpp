#include "AbstractTestShellApplication.h"
#include <algorithm>
#include <exception>
#include <sstream>
#include <string>
#include "ICommand.h"
#include "ICommandMapper.h"
#include "IView.h"

void AbstractTestShellApplication::InterpretUserCommandAndExecute(const std::string& userInput)
{
	// 2. Split User Input Command String
	std::vector<std::string> userInputCommand = SplitUserInputCommand(userInput);

	// 3. Parse Command
	std::shared_ptr<ICommand> command = nullptr;
	for (auto& commandMapper : _commandMappers)
	{
		if (false == commandMapper->IsSupport(userInputCommand))
			continue;

		command = commandMapper->GenerateCommand(userInputCommand);
		break;
	}

	// 4. Check if Failed to map command
	if (command == nullptr)
		throw std::exception{ "INVALID COMMAND" };

	// 5. Execute Command
	std::shared_ptr<IView> view = command->Execute();

	// 6. Print Result
	if (view)
		view->Render(_oStream);
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
