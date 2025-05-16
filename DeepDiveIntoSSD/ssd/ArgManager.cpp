#include "ArgManager.h"

std::vector<std::string> ArgManager::commandSplit(int argc, char* argv[]) {
	std::vector<std::string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	return args;
}

bool ArgManager::isValid(const std::vector<std::string>& args) {
	return true;
}

Arg ArgManager::makeStruct(const std::vector<std::string>& args) {
	Arg arg;

	return arg;
}