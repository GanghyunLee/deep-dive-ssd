#include "CommandBufferAlgorithm.h"

void CommandBufferAlgorithm::initStatus() {
	for (int i = 0; i < 100; i++) {
		status[i] = STATUS::CLEAN;
	}
}

void CommandBufferAlgorithm::getCurrentStatus(std::vector<Command>& buffer) {

	int cnt = getCommandCount(buffer);

	if (cnt <= 1) {
		return;
	}

	initStatus();

	for (int i = 0; i < cnt - 1; i++) {
		Command arg = buffer[i];

		switch (arg.type) {
		case ERASE:
			setStatusWithEraseCommand(arg);
			break;
		case WRITE:
			setStatusWithWriteCommand(arg);
			break;
		}
	}
}

int CommandBufferAlgorithm::getCommandCount(std::vector<Command>& buffer) {

	int cnt = 0;
	for (auto item : buffer) {
		if (item.type == EMPTY) {
			break;
		}
		cnt++;
	}

	return cnt;
}

int CommandBufferAlgorithm::getStatus(int index) {
	return status[index];
}

std::vector<Command> CommandBufferAlgorithm::ignoreCommand(std::vector<Command> buffer) {
	
	std::vector<Command> tmpBuffer;

	int cnt = getCommandCount(buffer);
	int idx = cnt - 1;
	Command latestArg = buffer[idx];
	int tempStatus[100] = { 0 };

	getCurrentStatus(buffer);
	updateStatus(latestArg, tempStatus);

	if (latestArg.type == WRITE) {
		if (status[latestArg.index] == MODIFIED) {
			for (int i = 0; i < idx; i++) {
				if (buffer[i].type != WRITE || buffer[i].index != latestArg.index) {
					tmpBuffer.push_back(buffer[i]);
				}
			}
			tmpBuffer.push_back(latestArg);
		}
		else if (status[latestArg.index] == ERASED) {
			for (int i = 0; i < idx; i++) {
				if (buffer[i].type == ERASE) {
					int startIdx = buffer[i].index;
					int endIdx = startIdx + stoi(buffer[i].value) - 1;
					if (startIdx == latestArg.index) {
						buffer[i].index += 1;
						buffer[i].value = std::to_string(stoi(buffer[i].value) - 1);
					}
					else if (endIdx == latestArg.index) {
						buffer[i].value = std::to_string(stoi(buffer[i].value) - 1);
					}
				}
				tmpBuffer.push_back(buffer[i]);
			}
			tmpBuffer.push_back(latestArg);
		}
		else {
			tmpBuffer = buffer;
		}
	}
	else if (latestArg.type == ERASE) {
		for (int i = 0; i < idx; i++) {
			if (!isErased(buffer[i], tempStatus)) {
				tmpBuffer.push_back(buffer[i]);
			}
		}
		if (!isErasedBigger(latestArg)) {
			tmpBuffer.push_back(latestArg);
		}
	}

	updateStatus(latestArg, status);

	cnt = 5 - tmpBuffer.size();
	for (int i = 0; i < cnt; i++) {
		tmpBuffer.push_back({ EMPTY, });
	}

	return tmpBuffer;
}

void CommandBufferAlgorithm::setStatusWithEraseCommand(Command arg) {
	
	int index = arg.index;
	int range = stoi(arg.value, nullptr, 10);

	for (int i = index; i < index + range; i++) {
		this->status[i] = ERASED;
	}
}

void CommandBufferAlgorithm::setStatusWithWriteCommand(Command arg) {
	this->status[arg.index] = MODIFIED;
}

void CommandBufferAlgorithm::updateStatus(Command arg, int* status) {
	int idx = arg.index;

	if (arg.type == WRITE) {
		status[idx] = MODIFIED;
	}
	else if (arg.type == ERASE) {
		int value = stoi(arg.value);
		int endidx = idx + value;

		for (int i = idx; i < endidx; i++) {
			status[i] = ERASED;
		}
	}
}

bool CommandBufferAlgorithm::isErased(Command arg, int* status) {
	if (arg.type == WRITE) {
		if (status[arg.index] == ERASED) {
			return true;
		}
	}
	else if (arg.type == ERASE) {
		int startIdx = arg.index;
		int endIdx = startIdx + stoi(arg.value);

		for (int i = startIdx; i < endIdx; i++) {
			if (status[i] != ERASED) {
				return false;
			}
		}
	}

	return true;
}

bool CommandBufferAlgorithm::isErasedBigger(Command arg) {
	int startIdx = arg.index;
	int endIdx = startIdx + stoi(arg.value);
	int lowEnd = startIdx - 1;

	for (int i = startIdx; i < endIdx; i++) {
		if (status[i] != ERASED) {
			return false;
		}
	}

	if (lowEnd >= 0) {
		if (status[lowEnd] == ERASED) {
			return true;
		}
	}

	if (endIdx < 100) {
		if (status[endIdx] == ERASED) {
			return true;
		}
	}

	return false;
}

bool CommandBufferAlgorithm::mergeAble(Command a, Command b) {

	if (a.type != ERASE || b.type != ERASE) {
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

bool CommandBufferAlgorithm::isContinuousEraseRange(Command a, Command b) {

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

bool CommandBufferAlgorithm::isAllErased(Command a, Command b) {

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

int CommandBufferAlgorithm::mergedRange(Command a, Command b) {

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

Command CommandBufferAlgorithm::mergeTwoCommand(Command a, Command b) {
	
	int startIdx = a.index;
	if (b.index < a.index) {
		startIdx = b.index;
	}

	int range = mergedRange(a, b);

	Command mergedCommand = { COMMAND_TYPE::ERASE, startIdx, std::to_string(range) };
	setStatusWithEraseCommand(mergedCommand);
	
	return mergedCommand;
}

std::vector<Command> CommandBufferAlgorithm::merge(const std::vector<Command> &buffer) {
	
	std::vector<Command> tmpBuffer = buffer;

	while (1) {

		// find merge item
		int idx1, idx2; 
		Command mergeCommand1, mergeCommand2;
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

		Command mergedCommand = mergeTwoCommand(mergeCommand1, mergeCommand2);
		tmpBuffer[idx2] = mergedCommand;
		
		tmpBuffer.erase(tmpBuffer.begin() + idx1);
		tmpBuffer.push_back({ COMMAND_TYPE::EMPTY, 0, "" });
	}

	return tmpBuffer;
}