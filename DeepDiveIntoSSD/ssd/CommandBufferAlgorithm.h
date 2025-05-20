#pragma once
#include <vector>
#include <string>
#include "ArgManager.h"

class CommandBufferAlgorithm {
public:
	std::vector<Arg> ignoreCommand(const std::vector<Arg>& buffer);

	std::vector<Arg> mergeErase(std::vector<Arg> buffer);

	Arg fastRead(std::vector<Arg> buffer);

	bool isIgnore(const std::vector<Arg>& buffer, int index);
private:
	std::vector<Arg> ret;
};