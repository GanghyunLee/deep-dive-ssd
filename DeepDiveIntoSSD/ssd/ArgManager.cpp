#include "ArgManager.h"

std::vector<std::string> ArgManager::commandSplit(int argc, char* argv[]) {
	std::vector<std::string> args;

	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	return args;
}

bool ArgManager::isValid(const std::vector<std::string>& args) {
	int argc = args.size();
	int index = stoi(args[1]);
	
	if (index > 99 || index < 0) return false;

	if (args[0] == "R") {
		if (argc > 2) return false;
	}
	else if (args[0] == "W") {
		if (argc > 3) return false;
		if (args[2].size() > 10) return false;

		if (args[2][0] != '0' && args[2][1] != 'x') return false;
		for (int i = 2; i < args[2].size(); i++) {
			if ((args[2][i] < '0' || args[2][i] > '9') && (args[2][i] < 'a' || args[2][i] > 'z')) return false;
		}
	}
	else {
		return false;
	}

	return true;
}

Arg ArgManager::makeStruct(const std::vector<std::string>& args) {
	Arg arg;

	if (args[0] == "R") {
		arg.RWflag = false;
		arg.index = stoi(args[1]);
		arg.value = "";
	}
	else {
		arg.RWflag = true;
		arg.index = stoi(args[1]);
		arg.value = args[2];
	}

	return arg;
}