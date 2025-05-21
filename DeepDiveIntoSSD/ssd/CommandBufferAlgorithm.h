#pragma once
#include <vector>
#include <string>
#include "ArgManager.h"

enum STATUS { CLEAN = 0, ERASED, MODIFIED };

class CommandBufferAlgorithm {
public:
	
	void initStatus();
	void getCurrentStatus(std::vector<Arg>& buffer);
	int getCommandCount(std::vector<Arg>& buffer);
	int getStatus(int index);


	std::vector<Arg> ignoreCommand(std::vector<Arg> buffer);
	std::vector<Arg> mergeErase(std::vector<Arg> buffer);



	bool mergeAble(Arg a, Arg b);
	bool isContinuousEraseRange(Arg a, Arg b);
	int mergedRange(Arg a, Arg b);
	Arg mergeTwoCommand(Arg a, Arg b);
	std::vector<Arg> merge(const std::vector<Arg> &buffer);

	Arg fastRead(std::vector<Arg> buffer);
private:
	std::vector<Arg> ret;
	int status[100] = { CLEAN, };
};