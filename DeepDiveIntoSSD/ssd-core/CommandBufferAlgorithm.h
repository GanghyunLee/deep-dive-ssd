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
	void setStatusWithEraseCommand(Arg arg);
	void setStatusWithWriteCommand(Arg arg);

	std::vector<Arg> ignoreCommand(std::vector<Arg> buffer);

	bool mergeAble(Arg a, Arg b);
	bool isContinuousEraseRange(Arg a, Arg b);
	bool isAllErased(Arg a, Arg b);

	int mergedRange(Arg a, Arg b);
	Arg mergeTwoCommand(Arg a, Arg b);
	std::vector<Arg> merge(const std::vector<Arg> &buffer);

	Arg fastRead(std::vector<Arg> buffer);

	void updateStatus(Arg arg, int* status);
	bool isErased(Arg arg, int* status);
	bool isErasedBigger(Arg arg);
	void setEmpty(std::vector<Arg>& buffer);
	void modifyEraseCommand(Arg& eraseArg, const Arg& latestArg);
private:
	std::vector<Arg> ret;
	int status[100] = { CLEAN, };
};