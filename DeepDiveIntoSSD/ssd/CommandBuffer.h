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
	Arg parseBufferNameToArg(const std::string& fileName);
	bool isBufferFull();
	std::vector<Arg> getBuffer();
	void pushBuffer(Arg arg);
	std::string makeBufferNameFromArg(Arg arg, int index);
	void updateBuffers(std::vector<Arg> b);
	int checkValueFromBuffer(int index);
	int fastRead(int index);
private:
	FileIO fileIO;
	ArgManager argManager;
	CommandBufferAlgorithm algo;
	std::vector<Arg> buffers;
};