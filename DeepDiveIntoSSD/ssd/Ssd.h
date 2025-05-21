#pragma once
#include <iostream>
#include <iomanip>

#include "FileIO.h"
#include "ArgManager.h"
#include "CommandBuffer.h"

class SSD {
public:
	static SSD& getInstance() {
		static SSD instance;
		return instance;
	}

	const std::string OUTPUT_FILE = "ssd_output.txt";
	const std::string INPUT_FILE = "ssd_nand.txt";

	void run(int argc, char* argv[]);

	void read(int index);
	void write(int index, std::string value);
	void erase(int index, std::string range);
	void flushBuffers();

	void updateData(int index, unsigned int value);

	void readAll();
	void dumpData();
	void dumpError();
	void dumpResult(int index, unsigned int value);
	void dumpSuccess();
	void initNand();

private:
	SSD(){
		m_argManager = new ArgManager();
	}
	SSD& operator=(const SSD& other) = delete;
	SSD(const SSD& other) = delete;
	ArgManager* m_argManager;
	FileIO* fileIO;
	unsigned int data[100] = { 0, };
	CommandBuffer* m_commandBuffer;
};