#pragma once

#include "ReaderWriter.h"
#include "ArgManager.h"
#include <iostream>
#include <iomanip>

class SSD {
public:
	const std::string OUTPUT_FILE = "ssd_output.txt";
	const std::string INPUT_FILE = "ssd_nand.txt";

	SSD(IReader* reader, IWriter* writer, ArgManager* argManager) : m_reader{ reader }, m_writer{ writer }, m_argManager{argManager} {}
	
	void run(int argc, char* argv[]);
	void read(int index);
	void write(int index, std::string value);
	void readAllData();
	void dumpData();
	void dumpError();

private:
	IReader* m_reader;
	IWriter* m_writer;
	ArgManager* m_argManager;
	FileIO* fileIO;
	int data[100] = { 0, };
};