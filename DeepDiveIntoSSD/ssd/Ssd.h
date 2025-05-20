#pragma once
#include <iostream>
#include <iomanip>

#include "FileIO.h"
#include "ArgManager.h"
#include "CommandBuffer.h"

class SSD {
public:
	const std::string OUTPUT_FILE = "ssd_output.txt";
	const std::string INPUT_FILE = "ssd_nand.txt";

	SSD(ArgManager* argManager) : m_argManager{ argManager } {}

	void run(int argc, char* argv[]);

	void read(int index);
	void write(int index, std::string value);
	void erase(int index, std::string range);

	void updateData(int index, unsigned int value);

	void readAll();
	void dumpData();
	void dumpError();
	void dumpResult(int index, unsigned int value);
	void dumpSuccess();

private:
	ArgManager* m_argManager;
	FileIO* fileIO;
	unsigned int data[100] = { 0, };
	CommandBuffer* m_commandBuffer;
};