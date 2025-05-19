#pragma once
#include <string>
#include <vector>
#include <ostream>

#include "IoC.h"

class TestShellApplication
{
public:
	TestShellApplication(IoC& ioc, std::istream& iStream, std::ostream& oStream, bool printShellPromptPrefix = false) :
		_ioc(ioc), _iStream(iStream), _oStream(oStream), _printShellPromptPrefix(printShellPromptPrefix) { }

public:
	bool Run();

protected:
	std::string GetUserInputLowerStr();
	std::vector<std::string> SplitCommand(const std::string& input);

private:
	const std::string STR_SHELL_START = "Shell>";
	const std::string EXIT_STRING = "exit";

private:
	IoC& _ioc;
	std::istream& _iStream;
	std::ostream& _oStream;
	bool _printShellPromptPrefix;
};

