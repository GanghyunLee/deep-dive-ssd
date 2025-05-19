#pragma once
#include <string>
#include <vector>
#include <ostream>

#include "IoC.h"

class TestShellApplication
{
public:
	TestShellApplication(std::vector<ICommandMapper*> commandMappers, std::istream& iStream, std::ostream& oStream, bool printShellPromptPrefix = true) :
		_commandMappers(commandMappers), _iStream(iStream), _oStream(oStream), _printShellPromptPrefix(printShellPromptPrefix) { }

public:
	bool Run();

protected:
	std::string GetUserInputLowerStr();
	std::vector<std::string> SplitUserInputCommand(const std::string& input);

private:
	const std::string STR_SHELL_START = "Shell>";
	const std::string EXIT_STRING = "exit";

private:
	std::vector<ICommandMapper*> _commandMappers;
	std::istream& _iStream;
	std::ostream& _oStream;
	bool _printShellPromptPrefix;
};

