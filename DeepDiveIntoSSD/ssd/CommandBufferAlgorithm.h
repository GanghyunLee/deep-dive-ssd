#pragma once
#include <vector>
#include <string>

class CommandBufferAlgorithm {
public:
	CommandBufferAlgorithm(std::vector<std::string> buffer) :
		buffer{ buffer } {}

	std::vector<std::string> ignoreCommand();

	std::vector<std::string> mergeErase();

	std::string fastRead();
private:
	std::vector<std::string> buffer;
};