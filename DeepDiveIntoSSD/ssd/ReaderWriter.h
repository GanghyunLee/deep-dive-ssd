#pragma once

#include <string>
#include <iostream>
#include "FileIO.h"

class IReader {
public:
	virtual void read(int index) = 0;
};

class IWriter {
public:
	virtual void write(int index, std::string value) = 0;
};

class Reader : public IReader {
public:
	void read(int index) override {
		if (fileIO.isInvalidArgument(INPUT_FILE, fileIO.READ_MODE))
			return;
		fileIO.setArgument(INPUT_FILE, fileIO.READ_MODE);
		fileIO.openFile();
		if (!fileIO.isOpen())
			return;
		fileIO.readLine();

		return;
	}
private:
	FileIO fileIO;
	const std::string INPUT_FILE = "sdd_nand.txt";
};

class Writer : public IWriter {
public:
	void write(int index, std::string value) override {
		if (fileIO.isInvalidArgument(OUTPUT_FILE, fileIO.WRITE_MODE))
			return;
		fileIO.setArgument(OUTPUT_FILE, fileIO.WRITE_MODE);
		fileIO.openFile();
		if (!fileIO.isOpen())
			return;
		fileIO.writeLine(value);
		return;
	}
private:
	FileIO fileIO;
	const std::string OUTPUT_FILE = "sdd_output.txt";
};
