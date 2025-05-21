#include "CommandBufferAlgorithm.h"

void CommandBufferAlgorithm::initStatus() {
	for (int i = 0; i < 100; i++) {
		status[i] = STATUS::CLEAN;
	}
}

void CommandBufferAlgorithm::getCurrentStatus(std::vector<Arg>& buffer) {

	// EMPTY 전까지 찾으면 됨.
	int cnt = getCommandCount(buffer);

	if (cnt <= 1) {
		return;
	}

	initStatus();

	for (int i = 0; i < cnt - 1; i++) {
		Arg arg = buffer[i];

		switch (arg.commandType) {
		case ERASE:
			
			for (int i = arg.index; i < arg.index + stoi(arg.value, nullptr, 10); i++) {
				status[i] = STATUS::ERASED;
			}

			break;

		case WRITE:
			status[arg.index] = MODIFIED;
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
	return ret;
}

std::vector<Arg> CommandBufferAlgorithm::mergeErase(std::vector<Arg> buffer) {
	return ret;
}

Arg CommandBufferAlgorithm::fastRead(std::vector<Arg> buffer) {
	Arg ret;

	return ret;
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

bool CommandBufferAlgorithm::isErased(Arg arg, int* status) {
	if (arg.commandType == WRITE) {
		if (status[arg.index] == ERASED) {
			return true;
		}
	}
	else if (arg.commandType == ERASE) {
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

bool CommandBufferAlgorithm::isErasedBigger(Arg arg) {
	int startIdx = arg.index;
	int endIdx = startIdx + stoi(arg.value);
	int lowEnd = startIdx - 1;

	for (int i = startIdx; i < endIdx; i++) {
		if (status[i] != ERASED) {
			return false;
		}
	}

	if (lowEnd >= 0) {
		if (status[lowEnd] != ERASED) {
			return false;
		}
	}

	if (endIdx < 100) {
		if (status[endIdx] != ERASED) {
			return false;
		}
	}

	return true;
}

bool CommandBufferAlgorithm::mergeAble(Arg a, Arg b) {

	if (a.commandType != ERASE || b.commandType != ERASE) {
		return false;
	}

	if (!isContinuousEraseRange(a, b)) {
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
	return { COMMAND_TYPE::ERASE, startIdx, std::to_string(range) };
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
		
		// erase and push back empty
		tmpBuffer.erase(tmpBuffer.begin() + idx1);
		tmpBuffer.push_back({ COMMAND_TYPE::EMPTY, 0, "" });

	}

	return tmpBuffer;
}

