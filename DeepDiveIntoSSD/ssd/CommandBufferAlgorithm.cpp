#include "CommandBufferAlgorithm.h"

void CommandBufferAlgorithm::setCommandBuffer(std::vector<std::string> buffer) {
	this->buffer = buffer;
}

std::vector<std::string> CommandBufferAlgorithm::ignoreCommand() {
	return ret;
}

std::vector<std::string> CommandBufferAlgorithm::mergeErase() {
	return ret;
}

std::string CommandBufferAlgorithm::fastRead() {
	std::string ret;

	return ret;
}

bool CommandBufferAlgorithm::mergeAble(Arg a, Arg b) {
	return false;
}

Arg CommandBufferAlgorithm::mergeTwoCommand(Arg a, Arg b) {
	Arg mergedArg;
	return mergedArg;
}

std::vector<Arg> CommandBufferAlgorithm::merge() {

	std::vector<Arg> a;


	return a;
}