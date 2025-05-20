#pragma once
#include <string>
#include <vector>

enum COMMAND_TYPE { READ = 1, WRITE, ERASE };

struct Arg {
public:
	// commandType
	// 1 = Read
	// 2 = Write
	// 3 = Erase
	int commandType;
	int index;
	std::string value;
};

class ArgManager {
public:
	std::vector<std::string> commandSplit(int argc, char* argv[]);
	Arg makeStruct(const std::vector<std::string>& args);
	bool isValid(std::vector<std::string>& args);
	bool outOfRangeIndex(int index);
	bool invalidCommand(const std::string &command);
};