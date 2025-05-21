#pragma once
#include "FileIO.h"
#include "ArgManager.h"
#include "CommandBufferAlgorithm.h"
#include <vector>

class CommandBuffer {
public:
	bool checkDirectory();
	void resetBuffer();
	void createBuffer();
	void loadBuffer();
	Command parseBufferNameToArg(const std::string& fileName);
	bool isBufferFull();
	std::vector<Command> getBuffer();
	void pushBuffer(Command arg);
	std::string makeBufferNameFromArg(Command arg, int index);
	void updateBuffers(std::vector<Command> b);
	int checkValueFromBuffer(int index);
	int fastRead(int index);
private:
	FileIO fileIO;
	ArgManager argManager;
	CommandBufferAlgorithm algo;
	std::vector<Command> buffers;
};