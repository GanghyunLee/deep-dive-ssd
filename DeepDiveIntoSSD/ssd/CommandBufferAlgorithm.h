#pragma once
#include <vector>
#include <string>
#include "ArgManager.h"

class CommandBufferAlgorithm {
public:
	std::vector<Arg> ignoreCommand(std::vector<Arg> buffer);

	std::vector<Arg> mergeErase(std::vector<Arg> buffer);

	Arg fastRead(std::vector<Arg> buffer);
private:
	std::vector<Arg> ret;
};