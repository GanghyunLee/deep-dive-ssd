﻿#pragma once
#include <string>
#include <vector>
#include <ostream>

#include "ILogger.h"
#include "IoC.h"

class AbstractTestShellApplication
{
public:
	AbstractTestShellApplication(const std::vector<std::shared_ptr<ICommandMapper>>& commandMappers, std::istream& iStream, std::shared_ptr<ILogger> logger, bool printShellPromptPrefix = true) :
		_commandMappers(commandMappers), _iStream(iStream), _logger(logger), _printShellPromptPrefix(printShellPromptPrefix) {
	}
	virtual ~AbstractTestShellApplication() = default;

public:
	virtual bool Run(int argc, char* argv[]) = 0;

protected:
	std::shared_ptr<ICommand> FindMatchingCommand(const std::string& userInput);
	std::vector<std::string> SplitUserInputCommand(const std::string& input);

protected:
	std::vector<std::shared_ptr<ICommandMapper>> _commandMappers;
	std::istream& _iStream;
	std::shared_ptr<ILogger> _logger;
	bool _printShellPromptPrefix;
};

