#pragma once
#include <vector>
#include <string>

class CommandBufferAlgorithm {
public:
	CommandBufferAlgorithm() {}
	CommandBufferAlgorithm(std::vector<std::string> buffer) :
		buffer{ buffer } {}

	void setCommandBuffer(std::vector<std::string> buffer);

	std::vector<std::string> ignoreCommand();

	std::vector<std::string> mergeErase();

	std::string fastRead();
private:
	std::vector<std::string> buffer;
	std::vector<std::string> ret;
};