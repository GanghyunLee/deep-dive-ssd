#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "ReaderWriter.h"
#include "FileIO.h"

int Reader::read(int index)  {

	fileIO = new FileIO();
	fileIO->setArgument("ssd_nand.txt", fileIO->READ_MODE);
	fileIO->openFile();

	int data[100] = { 0, };

	while (true) {
		std::string line = fileIO->readLine();

		if (line == fileIO->EOF_STRING) {
			break;
		}

		std::stringstream ss(line);
		int idx, value;

		ss >> std::dec >> idx;
		ss >> std::hex >> value;

		data[idx] = value;
	}

	fileIO->closeFile();
	updateOutputFile(index, data[index]);

	return data[index];
}

void Reader::updateOutputFile(int index, int value) {

	std::fstream file("ssd_output.txt", std::ios::out);
	file << "0x" << std::hex << std::setfill('0') << std::setw(10) << value;

	return;
}


void Writer::write(int index, const std::string& value) {
	return;
}
