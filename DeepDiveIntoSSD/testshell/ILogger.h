#pragma once
#include <string>

class ILogger
{
public:
	virtual ~ILogger() = default;

public:
	virtual void print(const std::string& className, const std::string& functionName,
		const std::string& message, bool printLogInfo = true) = 0;

	virtual void printLine() = 0;
	virtual std::ostream& getMainOstream() = 0;
};
