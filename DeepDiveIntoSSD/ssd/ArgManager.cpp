#include "ArgManager.h"

std::vector<std::string> ArgManager::commandSplit(int argc, char* argv[]) {
	std::vector<std::string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	return args;
}

bool ArgManager::isValid(std::vector<std::string>& args) {
	int argc = args.size();
	int index = stoi(args[1]);
	
	if (index > 99 || index < 0) return false;

	if (args[0] == "R" || args[0] == "r") {
		if (argc != 2) return false;
	}
	else if (args[0] == "W" || args[0] == "w") {
		if (argc != 3) return false;
		if (args[2].size() > 10) return false;
		if (args[2][0] != '0' && args[2][1] != 'x') return false;
		for (int i = 2; i < args[2].size(); i++) {
			if ((args[2][i] < '0' || args[2][i] > '9') && (args[2][i] < 'a' || args[2][i] > 'f') && (args[2][i] < 'A' || args[2][i] > 'F')) return false;
			if (args[2][i] >= 'a' && args[2][i] <= 'f') {
				args[2][i] -= 32;
			}
		}
	}
	else {
		return false;
	}

	return true;
}

Arg ArgManager::makeStruct(const std::vector<std::string>& args) {
	Arg arg;
	arg.index = stoi(args[1]);
	
	if (args[0] == "R" || args[0] == "r") {
		arg.isWrite = false;
		arg.value = "";
	}
	else {
		int digits = 10 - args[2].size();
		arg.isWrite = true;
		arg.value = args[2];
		for (int i = 0; i < digits; i++) {
			arg.value.insert(2, "0");
		}
	}

	return arg;
}