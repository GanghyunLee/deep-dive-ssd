#pragma once
#include <string>
#include <vector>

enum COMMAND_TYPE { EMPTY = 0, READ , WRITE, ERASE, FLUSH };

struct Command {
public:
	int commandType;
	int index;
	std::string value;

	bool operator == (const Command& arg) const {
		if (this->commandType != arg.commandType) return false;
		if (this->index != arg.index) return false;
		if (this->value != arg.value) return false;
		return true;
	}
};

class ArgManager {
public:
	std::vector<std::string> commandSplit(int argc, char* argv[]);
	Command makeStruct(const std::vector<std::string>& args);
	bool isValid(std::vector<std::string>& args);
	bool outOfRangeIndex(int index);
	bool invalidCommand(const std::string& command);
};