#pragma once
#include <string>
#include <vector>

struct Arg {
public:
	bool isWrite;
	int index;
	std::string value;
};

class ArgManager {
public:
	std::vector<std::string> commandSplit(int argc, char* argv[]);
	Arg makeStruct(const std::vector<std::string>& args);
	bool isValid(std::vector<std::string>& args);
};