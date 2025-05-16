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
	std::vector<std::string> GetUserInputLowerStr();

private:
	const std::string STR_SHELL_START = "Shell>";

private:
	IoC& _ioc;
	std::istream& _iStream;
	std::ostream& _oStream;
	bool _printShellPromptPrefix;
};

