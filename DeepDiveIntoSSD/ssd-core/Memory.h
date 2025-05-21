#pragma once
#include <sstream>
#include <iostream>
#include <iomanip>
#include "FileIO.h"

class IMemory {
public:
	virtual void init() = 0;
	virtual void readAll() = 0;
	virtual void readOne(int index) = 0;
	virtual void dumpData() = 0;
	virtual void dumpError() = 0;
	virtual void dumpResult(int index, unsigned int value) = 0;
	virtual void dumpSuccess() = 0;
	virtual void updateData(int index, unsigned int value) = 0;
};

class FileMemory : public IMemory {
public:
	void init() override {
		if (!fileIO.checkFileExist(INPUT_FILE)) {
			dumpData();
		}
	}

	void readOne(int index) override {
		readAll();
		dumpResult(index, data[index]);
	}

	void readAll() override {
		fileIO.setArgument(INPUT_FILE, fileIO.READ_MODE);
		fileIO.openFile();

		while (true) {

			std::string line = fileIO.readLine();

			if (line == fileIO.EOF_STRING) {
				break;
			}

			std::stringstream ss(line);
			int index;
			unsigned int value;
			ss >> std::dec >> index;
			ss >> std::hex >> value;

			data[index] = value;
		}

		fileIO.closeFile();
	}

	void dumpData() override {
		fileIO.setArgument(INPUT_FILE, fileIO.WRITE_TRUNC_MODE);
		fileIO.openFile();

		for (int i = 0; i < 100; i++) {
			std::stringstream ss;
			ss << std::dec << std::setfill('0') << std::setw(2) << i;
			ss << " 0x";
			ss << std::hex << std::setfill('0') << std::setw(8) << std::nouppercase << data[i];

			fileIO.writeLine(ss.str());
		}

		fileIO.closeFile();

		return;
	}

	void dumpError() override {
		fileIO.setArgument(OUTPUT_FILE, fileIO.WRITE_TRUNC_MODE);
		fileIO.openFile();
		fileIO.writeLine("ERROR");
		fileIO.closeFile();
		return;
	}

	void dumpResult(int index, unsigned int value) override {
		std::fstream file(OUTPUT_FILE, std::ios::out | std::ios::trunc);
		file << "0x" << std::hex << std::setfill('0') << std::setw(8) << value;
		file.close();
	}

	void dumpSuccess() override {
		fileIO.setArgument(OUTPUT_FILE, fileIO.WRITE_TRUNC_MODE);
		fileIO.openFile();
		fileIO.writeLine("");
		fileIO.closeFile();
		return;
	}

	void updateData(int index, unsigned int value) override {
		data[index] = value;
	}

private:
	FileIO fileIO;
	const std::string OUTPUT_FILE = "ssd_output.txt";
	const std::string INPUT_FILE = "ssd_nand.txt";
	unsigned int data[100] = { 0, };
};

class RealMemory : public IMemory {
public:
	void init() {}
	void readAll() {}
	void readOne(int index) {}
	void dumpData() {}
	void dumpError() {}
	void dumpResult(int index, unsigned int value) {}
	void dumpSuccess() {}
	void updateData(int index, unsigned int value) {}
};

class MemoryFactory {
public:
	IMemory* createFileMemoryForSSD() {
		return new FileMemory();
	}
	IMemory* createRealMemoryForSSD() {
		return new RealMemory();
	}
};