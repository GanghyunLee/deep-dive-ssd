#pragma once
#include <string>

class ILogger
{
protected:
	enum : bool
	{
		DEFAULT_PRINT_LOG_INFO_VALUE = true,
	};
public:
	virtual ~ILogger() = default;

public:
	virtual void print(const std::string& className, const std::string& functionName,
		const std::string& message, bool printLogInfo = DEFAULT_PRINT_LOG_INFO_VALUE, int printdir = 0) = 0;

	virtual void printLine() = 0;
	virtual std::ostream& getMainOstream() = 0;
};
