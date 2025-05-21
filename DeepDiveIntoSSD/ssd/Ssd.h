#pragma once
#include <iostream>
#include <iomanip>

#include "FileIO.h"
#include "ArgManager.h"
#include "CommandBuffer.h"
#include "Memory.h"

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

	void initNand();

private:
	SSD(){
		m_argManager = new ArgManager();
		initNand();
	}
	SSD& operator=(const SSD& other) = delete;
	SSD(const SSD& other) = delete;
	ArgManager* m_argManager;
	CommandBuffer* m_commandBuffer;
	IMemory* memory;
	MemoryFactory memoryFactory;
};