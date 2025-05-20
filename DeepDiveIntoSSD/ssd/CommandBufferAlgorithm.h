#pragma once
#include <vector>
#include <string>
#include "ArgManager.h"

class CommandBufferAlgorithm {
public:
	std::vector<Arg> ignoreCommand(std::vector<Arg> buffer);
	std::vector<Arg> mergeErase(std::vector<Arg> buffer);

	bool mergeAble(Arg a, Arg b);
	Arg mergeTwoCommand(Arg a, Arg b);
	std::vector<Arg> merge();

	Arg fastRead(std::vector<Arg> buffer);
private:
	std::vector<Arg> ret;
};