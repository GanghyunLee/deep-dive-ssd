#pragma once
#include "ILogger.h"
#include <ostream>

class InMemoryLogger : public ILogger
{
public:
	InMemoryLogger(std::ostream& ostream) : _ostream(ostream)
	{
	}
	~InMemoryLogger() override = default;

	InMemoryLogger(const InMemoryLogger&) = delete;
	InMemoryLogger& operator=(const InMemoryLogger&) = delete;


public:
	void print(const std::string& className, const std::string& functionName, const std::string& message,
		bool printLogInfo = DEFAULT_PRINT_LOG_INFO_VALUE, int printdir = 0) override;
	void printLine() override;
	std::ostream& getMainOstream() override { return _ostream; }

protected:
	std::ostream& _ostream;
};

