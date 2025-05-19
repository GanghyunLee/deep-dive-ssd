#pragma once

#include "ReaderWriter.h"
#include "ArgManager.h"
#include <iostream>
#include <iomanip>

class SSD {
public:
	SSD(IReader* reader, IWriter* writer, ArgManager* argManager) : m_reader{ reader }, m_writer{ writer }, m_argManager{argManager} {}
	
	void run(int argc, char* argv[]);
	void read(int index);
	void write(int index, std::string value);
	void initFile();

private:
	IReader* m_reader;
	IWriter* m_writer;
	ArgManager* m_argManager;
};