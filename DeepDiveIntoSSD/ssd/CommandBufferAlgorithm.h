#pragma once
#include <vector>
#include <string>

#include "ArgManager.h"

class CommandBufferAlgorithm {
public:
	CommandBufferAlgorithm() {}
	CommandBufferAlgorithm(std::vector<std::string> buffer) :
		buffer{ buffer } {}

	void setCommandBuffer(std::vector<std::string> buffer);

	std::vector<std::string> ignoreCommand();

	std::vector<std::string> mergeErase();
	std::string fastRead();

	bool mergeAble(Arg a, Arg b);
	Arg mergeTwoCommand(Arg a, Arg b);
	std::vector<Arg> merge();

private:
	std::vector<std::string> buffer;
	std::vector<std::string> ret;
};