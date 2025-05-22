#include "ArgManager.h"
#include <stdexcept>

std::vector<std::string> ArgManager::commandSplit(int argc, char* argv[]) {
	std::vector<std::string> args;
	for (int i = 0; i < argc; i++) {
		args.push_back(std::string(argv[i]));
	}

	return args;
}

bool ArgManager::isValid(std::vector<std::string>& args) {
	int argc = args.size();
	int index = 0;
	char cmd;

	if (argc == 0) {
		return false;
	}

	if (invalidCommand(args[0])) {
		return false;
	}

	cmd = toupper(args[0][0]);

	if (cmd == 'F') {
		return isValidFlush(argc);
	}

	if (argc < 2) return false;

	// args[1]의 값이 int로 바꿀 수 없는 값일 경우 invalid_argument exception 발생
	try {
		index = stoi(args[1]);
	}
	catch (const std::invalid_argument& e) {
		return false;
	}

	if (outOfRangeIndex(index)) {
		return false;
	}

	if (cmd == 'R') {
		return isValidRead(argc);
	}

	if (argc != 3) return false;

	if (cmd == 'W') {
		return isValidWrite(args);
	}

	if (cmd == 'E') {
		return isValidErase(args);
	}

	return true;
}

bool ArgManager::isValidFlush(int argc)
{
	return argc == 1;
}

bool ArgManager::isValidRead(int argc)
{
	return argc == 2;
}

bool ArgManager::isValidWrite(std::vector<std::string>& args) {
	//hexadecimal check

	if (args[2].size() > 10 || args[2].size() < 3) return false;
	if (args[2][0] != '0' && args[2][1] != 'x') return false;

	for (int i = 2; i < args[2].size(); i++) {
		if ((args[2][i] < '0' || args[2][i] > '9') && (args[2][i] < 'a' || args[2][i] > 'f') && (args[2][i] < 'A' || args[2][i] > 'F')) return false;
		if (args[2][i] >= 'a' && args[2][i] <= 'f') {
			args[2][i] -= 32;
		}
	}

	return true;
}

bool ArgManager::isValidErase(const std::vector<std::string>& args) {
	int erase_range = std::stoi(args[2]);

	return (erase_range >= 0 && erase_range <= 10);
}

bool ArgManager::outOfRangeIndex(int index) {
	return index > 99 || index < 0;
}

bool ArgManager::invalidCommand(const std::string& command) {
	return command != "R" && command != "r" && command != "W" && command != "w" &&
		command != "E" && command != "e" && command != "F" && command != "f";
}

Arg ArgManager::makeStruct(const std::vector<std::string>& args) {
	Arg arg;

	if (args.size() == 0 || args[0] == "empty") {
		arg.commandType = COMMAND_TYPE::EMPTY;
		arg.value = "";
		return arg;
	}

	if (args[0] == "F" || args[0] == "f") {
		arg.commandType = COMMAND_TYPE::FLUSH;
		arg.value = "";
		return arg;
	}

	arg.index = stoi(args[1]);

	if (args[0] == "R" || args[0] == "r") {
		arg.commandType = COMMAND_TYPE::READ;
		arg.value = "";

		return arg;
	}

	if (args[0] == "W" || args[0] == "w") {
		int digits = 10 - args[2].size();
		arg.commandType = COMMAND_TYPE::WRITE;
		arg.value = args[2];
		for (int i = 0; i < digits; i++) {
			arg.value.insert(2, "0");
		}

		return arg;
	}

	if (args[0] == "E" || args[0] == "e") {
		arg.commandType = COMMAND_TYPE::ERASE;
		arg.value = args[2];
		return arg;
	}

	return arg;
}