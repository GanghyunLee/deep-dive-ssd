#pragma once
#include <vector>
#include <string>
#include "ArgManager.h"

class CommandBufferAlgorithm {
public:
	std::vector<Arg> ignoreCommand(const std::vector<Arg>& buffer);
  
	std::vector<Arg> mergeErase(std::vector<Arg> buffer);

	bool mergeAble(Arg a, Arg b);
	bool isContinuousEraseRange(Arg a, Arg b);
	int mergedRange(Arg a, Arg b);
	Arg mergeTwoCommand(Arg a, Arg b);
	std::vector<Arg> merge();

	Arg fastRead(std::vector<Arg> buffer);

	bool isIgnore(const std::vector<Arg>& buffer, int index);
private:
	std::vector<Arg> ret;
};