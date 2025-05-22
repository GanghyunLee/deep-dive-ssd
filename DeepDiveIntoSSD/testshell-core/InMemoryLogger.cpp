#include "InMemoryLogger.h"

void InMemoryLogger::print(const std::string& className, const std::string& functionName, const std::string& message,
	bool printLogInfo, int printdir)
{
	_ostream << message;
}

void InMemoryLogger::printLine()
{
	_ostream << '\n';
}
