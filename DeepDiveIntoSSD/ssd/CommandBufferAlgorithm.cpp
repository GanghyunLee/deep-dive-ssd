#include "CommandBufferAlgorithm.h"

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

bool CommandBufferAlgorithm::mergeAble(Arg a, Arg b) {

	if (a.commandType != ERASE || b.commandType != ERASE) {
		return false;
	}

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
	for(int i = startIdx; i <= endIdx ; i++){
		if ( !(_a[i] || _b[i])) {
			isContinuous = false;
			break;
		}
	}

	if (!isContinuous) {
		return false;
	}

	int mergedRange = endIdx - startIdx + 1;
	
	if (mergedRange > 10) {
		return false;
	}

	return true;
}

Arg CommandBufferAlgorithm::mergeTwoCommand(Arg a, Arg b) {
	Arg mergedArg;
	return mergedArg;
}

std::vector<Arg> CommandBufferAlgorithm::merge() {

	std::vector<Arg> a;


	return a;
}