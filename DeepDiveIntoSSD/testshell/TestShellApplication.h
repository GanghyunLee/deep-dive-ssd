#pragma once
#include <string>
#include <vector>
#include <ostream>

#include "AbstractTestShellApplication.h"
#include "IoC.h"

class TestShellApplication : public AbstractTestShellApplication
{
public:
	TestShellApplication(const std::vector<std::shared_ptr<ICommandMapper>>& commandMappers, std::istream& iStream, std::ostream& oStream, bool printShellPromptPrefix = true) :
		AbstractTestShellApplication(commandMappers, iStream, oStream, printShellPromptPrefix) { }

public:
	bool Run(int argc, char* argv[]) override;

protected:
	std::string GetUserInputLowerStr();

private:
	const std::string STR_SHELL_START = "Shell>";
	const std::string EXIT_STRING = "exit";
};

