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