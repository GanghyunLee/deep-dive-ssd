#pragma once

#include <string>
#include <iostream>
#include "FileIO.h"

class IReader {
public:
	virtual int read(int index) = 0;
};

class IWriter {
public:
	virtual void write(int index, const std::string& value) = 0;
};

class Reader : public IReader {
public:
	int read(int index) override;
private:
	FileIO *fileIO;
	const std::string INPUT_FILE = "ssd_nand.txt";
};

class Writer : public IWriter {
public:
	void write(int index, const std::string& value) override;

private:
	FileIO *fileIO;
	const std::string OUTPUT_FILE = "ssd_output.txt";
};