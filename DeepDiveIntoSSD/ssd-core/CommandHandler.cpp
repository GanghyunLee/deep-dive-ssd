#include "CommandHandler.h"

std::vector<Arg> WriteCommandHandler::handle(std::vector<Arg>& buffer, int cnt, const Arg& latestArg, int* tempStatus, int* status) {
	std::vector<Arg> ret;
	int idx = cnt - 1;

	if (status[latestArg.index] == MODIFIED) {
		for (int i = 0; i < idx; i++) {
			if (buffer[i].commandType != WRITE || buffer[i].index != latestArg.index) {
				ret.push_back(buffer[i]);
			}
		}
		ret.push_back(latestArg);
	}
	else if (status[latestArg.index] == ERASED) {
		for (int i = 0; i < idx; i++) {
			if (buffer[i].commandType == ERASE) {
				modifyEraseCommand(buffer[i], latestArg);
			}
			ret.push_back(buffer[i]);
		}
		ret.push_back(latestArg);
	}
	else {
		ret = buffer;
	}

	return ret;
}

void WriteCommandHandler::modifyEraseCommand(Arg& eraseArg, const Arg& latestArg) {
	int startIdx = eraseArg.index;
	int endIdx = startIdx + stoi(eraseArg.value) - 1;

	if (startIdx == latestArg.index) {
		eraseArg.index += 1;
		eraseArg.value = std::to_string(stoi(eraseArg.value) - 1);
	}
	else if (endIdx == latestArg.index) {
		eraseArg.value = std::to_string(stoi(eraseArg.value) - 1);
	}
}

std::vector<Arg> EraseCommandHandler::handle(std::vector<Arg>& buffer, int cnt, const Arg& latestArg, int* tempStatus, int* status) {
	std::vector<Arg> ret;
	int idx = cnt - 1;

	for (int i = 0; i < idx; i++) {
		if (!isErased(buffer[i], tempStatus)) {
			ret.push_back(buffer[i]);
		}
	}
	if (!isErasedBigger(latestArg, status)) {
		ret.push_back(latestArg);
	}

	return ret;
}

bool EraseCommandHandler::isErased(const Arg& arg, int* status) {
	if (arg.commandType == WRITE) {
		return status[arg.index] == ERASED;
	}
	else if (arg.commandType == ERASE) {
		int start = arg.index;
		int end = start + std::stoi(arg.value);
		for (int i = start; i < end; ++i) {
			if (status[i] != ERASED) return false;
		}
	}
	return true;
}

bool EraseCommandHandler::isErasedBigger(const Arg& arg, int* status) {
	int start = arg.index;
	int end = start + std::stoi(arg.value);

	for (int i = start; i < end; i++) {
		if (status[i] != ERASED) return false;
	}

	if (start - 1 >= 0 && status[start - 1] == ERASED) return true;
	if (end < 100 && status[end] == ERASED) return true;

	return false;
}