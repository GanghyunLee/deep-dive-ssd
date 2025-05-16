#pragma once
#include <string>
#include <vector>

struct Arg {
public:
	bool RWflag;
	int index;
	std::string value;
};

class ArgManager {
public:
	std::vector<std::string> commandSplit(int argc, char* argv[]);
	Arg makeStruct(std::vector<std::string>);
	bool isValid(std::vector<std::string>);
};