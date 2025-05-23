#include "CommandBufferAlgorithm.h"

void CommandBufferAlgorithm::initStatus() {
	for (int i = 0; i < 100; i++) {
		status[i] = STATUS::CLEAN;
	}
}

void CommandBufferAlgorithm::getCurrentStatus(std::vector<Arg>& buffer) {

	int cnt = getCommandCount(buffer);

	if (cnt <= 1) {
		return;
	}

	initStatus();

	for (int i = 0; i < cnt - 1; i++) {
		Arg arg = buffer[i];

		switch (arg.commandType) {
		case ERASE:
			setStatusWithEraseCommand(arg);
			break;
		case WRITE:
			setStatusWithWriteCommand(arg);
			break;
		}
	}
}

int CommandBufferAlgorithm::getCommandCount(std::vector<Arg>& buffer) {

	int cnt = 0;
	for (auto item : buffer) {
		if (item.commandType == EMPTY) {
			break;
		}
		cnt++;
	}

	return cnt;
}

int CommandBufferAlgorithm::getStatus(int index) {
	return status[index];
}

std::vector<Arg> CommandBufferAlgorithm::ignoreCommand(std::vector<Arg> buffer) {
	int cnt = getCommandCount(buffer);
	Arg latestArg = buffer[cnt - 1];
	int tempStatus[100] = { 0 };

	getCurrentStatus(buffer);
	updateStatus(latestArg, tempStatus);

	if (latestArg.commandType == WRITE) {
		commandHandler = new WriteCommandHandler;
		ret = commandHandler->handle(buffer, cnt, latestArg, tempStatus, status);
	}
	else if (latestArg.commandType == ERASE) {
		commandHandler = new EraseCommandHandler;
		ret = commandHandler->handle(buffer, cnt, latestArg, tempStatus, status);
	}

	updateStatus(latestArg, status);

	setEmpty(ret);

	return ret;
}

void CommandBufferAlgorithm::setEmpty(std::vector<Arg>& buffer) {
	int cnt = 5 - buffer.size();

	for (int i = 0; i < cnt; i++) {
		buffer.push_back({ EMPTY, });
	}
}

void CommandBufferAlgorithm::modifyEraseCommand(Arg& eraseArg, const Arg& latestArg) {
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

void CommandBufferAlgorithm::setStatusWithEraseCommand(Arg arg) {
	
	int index = arg.index;
	int range = stoi(arg.value, nullptr, 10);

	for (int i = index; i < index + range; i++) {
		this->status[i] = ERASED;
	}
}

void CommandBufferAlgorithm::setStatusWithWriteCommand(Arg arg) {
	this->status[arg.index] = MODIFIED;
}

void CommandBufferAlgorithm::updateStatus(Arg arg, int* status) {
	int idx = arg.index;

	if (arg.commandType == WRITE) {
		status[idx] = MODIFIED;
	}
	else if (arg.commandType == ERASE) {
		int value = stoi(arg.value);
		int endidx = idx + value;

		for (int i = idx; i < endidx; i++) {
			status[i] = ERASED;
		}
	}
}

bool CommandBufferAlgorithm::mergeAble(Arg a, Arg b) {

	if (a.commandType != ERASE || b.commandType != ERASE) {
		return false;
	}

	if (!isContinuousEraseRange(a, b)) {
		return false;
	}

	if (!isAllErased(a, b)) {
		return false;
	}

	int range = mergedRange(a, b);
	if (range > 10) {
		return false;
	}

	return true;
}

bool CommandBufferAlgorithm::isContinuousEraseRange(Arg a, Arg b) {

	int a_range = stoi(a.value, nullptr, 10);
	int b_range = stoi(b.value, nullptr, 10);

	bool _a[100] = { 0, };
	bool _b[100] = { 0, };

	for (int i = a.index; i < a.index + a_range; i++) {
		_a[i] = true;
	}

	for (int i = b.index; i < b.index + b_range; i++) {
		_b[i] = true;
	}

	int startIdx = a.index;
	if (a.index > b.index) {
		startIdx = b.index;
	}

	int endIdx = a.index + a_range - 1;
	if (a.index + a_range - 1 < b.index + b_range - 1) {
		endIdx = b.index + b_range - 1;
	}

	bool isContinuous = true;
	for (int i = startIdx; i <= endIdx; i++) {
		if (!(_a[i] || _b[i])) {
			isContinuous = false;
			break;
		}
	}

	return isContinuous;
}

bool CommandBufferAlgorithm::isAllErased(Arg a, Arg b) {

	int a_range = stoi(a.value, nullptr, 10);
	int b_range = stoi(b.value, nullptr, 10);
	
	int startIdx = a.index;
	if (a.index > b.index) {
		startIdx = b.index;
	}

	int endIdx = a.index + a_range - 1;
	if (a.index + a_range - 1 < b.index + b_range - 1) {
		endIdx = b.index + b_range - 1;
	}

	for (int i = startIdx; i <= endIdx; i++) {
		if (status[i] != STATUS::ERASED) {
			return false;
		}
	}

	return true;
}

int CommandBufferAlgorithm::mergedRange(Arg a, Arg b) {

	int a_range = stoi(a.value, nullptr, 10);
	int b_range = stoi(b.value, nullptr, 10);

	int startIdx = a.index;
	if (a.index > b.index) {
		startIdx = b.index;
	}

	int endIdx = a.index + a_range - 1;
	if (a.index + a_range - 1 < b.index + b_range - 1) {
		endIdx = b.index + b_range - 1;
	}

	return endIdx - startIdx + 1;
}

Arg CommandBufferAlgorithm::mergeTwoCommand(Arg a, Arg b) {
	
	int startIdx = a.index;
	if (b.index < a.index) {
		startIdx = b.index;
	}

	int range = mergedRange(a, b);

	Arg mergedCommand = { COMMAND_TYPE::ERASE, startIdx, std::to_string(range) };
	setStatusWithEraseCommand(mergedCommand);
	
	return mergedCommand;
}

std::vector<Arg> CommandBufferAlgorithm::merge(const std::vector<Arg> &buffer) {
	
	std::vector<Arg> tmpBuffer = buffer;

	while (1) {

		// find merge item
		int idx1, idx2; 
		Arg mergeCommand1, mergeCommand2;
		bool find = false;

		for (int i = 0; i < tmpBuffer.size() - 1; i++) {
			mergeCommand1 = tmpBuffer[i];
			idx1 = i;
			for (int j = i + 1; j < tmpBuffer.size(); j++) {
				mergeCommand2 = tmpBuffer[j];
				idx2 = j;
				if (mergeAble(mergeCommand1, mergeCommand2)) {
					find = true;
					break;
				}
			}

			if (find) break;
		}

		if (!find) break;

		Arg mergedCommand = mergeTwoCommand(mergeCommand1, mergeCommand2);
		tmpBuffer[idx2] = mergedCommand;
		
		tmpBuffer.erase(tmpBuffer.begin() + idx1);
		tmpBuffer.push_back({ COMMAND_TYPE::EMPTY, 0, "" });
	}

	return tmpBuffer;
}