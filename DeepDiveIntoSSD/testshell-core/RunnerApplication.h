#pragma once
#include "AbstractTestShellApplication.h"

class RunnerApplication : public AbstractTestShellApplication
{
public:
	RunnerApplication(const std::vector<std::shared_ptr<ICommandMapper>>& commandMappers, std::istream& iStream, std::shared_ptr<ILogger> logger, bool printShellPromptPrefix = true) :
		AbstractTestShellApplication(commandMappers, iStream, logger, printShellPromptPrefix) {
	}
	~RunnerApplication() override = default;

public:
	bool Run(int argc, char* argv[]) override;
};

