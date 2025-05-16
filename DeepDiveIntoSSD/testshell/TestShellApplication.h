#pragma once
#include <string>
#include <vector>
#include <ostream>

#include "IoC.h"

class TestShellApplication
{
public:
	TestShellApplication(IoC& ioc, std::istream& iStream, std::ostream& oStream) :
		_ioc(ioc), _iStream(iStream), _oStream(oStream) { }

public:
	bool Run();
	std::vector<std::string> GetUserInput();

private:
	const std::string STR_SHELL_START = "Shell>";

private:
	IoC& _ioc;
	std::istream& _iStream;
	std::ostream& _oStream;
};

