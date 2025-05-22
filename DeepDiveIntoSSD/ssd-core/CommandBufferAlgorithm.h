#pragma once
#include <vector>
#include <string>
#include "ArgManager.h"

enum STATUS { CLEAN = 0, ERASED, MODIFIED };

class CommandBufferAlgorithm {
public:
	void initStatus();
	void getCurrentStatus(std::vector<Command>& buffer);
	
	int getCommandCount(std::vector<Command>& buffer);
	int getStatus(int index);
	void setStatusWithEraseCommand(Command arg);
	void setStatusWithWriteCommand(Command arg);

	std::vector<Command> ignoreCommand(std::vector<Command> buffer);

	bool mergeAble(Command a, Command b);
	bool isContinuousEraseRange(Command a, Command b);
	bool isAllErased(Command a, Command b);

	int mergedRange(Command a, Command b);
	Command mergeTwoCommand(Command a, Command b);
	std::vector<Command> merge(const std::vector<Command> &buffer);

	Command fastRead(std::vector<Command> buffer);

	void updateStatus(Arg arg, int* status);
	bool isErased(Arg arg, int* status);
	bool isErasedBigger(Arg arg);
	void setEmpty(std::vector<Arg>& buffer);
	void modifyEraseCommand(Arg& eraseArg, const Arg& latestArg);
private:
	int status[100] = { CLEAN, };
};