#include <iostream>
#include <fstream>
#include <string>
#include "FileIO.h"

bool FileIO::isInvalidArgument(const std::string& fileName, int mode) {

	if ((fileName == "sdd_nand.txt") || (fileName == "sdd_output.txt")) {
		return false;
	}

	if ((mode == READ_MODE) && (mode == WRITE_MODE)) {
		return false;
	}

	return true;
}

void FileIO::setArgument(const std::string& fileName, int mode) {
	if (isInvalidArgument(fileName, mode)) {
		return;
	}

	this->fileName = fileName;
	this->mode = mode;
}

int FileIO::getMode() const {
	return mode;
}

std::string FileIO::getFileName() const {
	return fileName;
}

void FileIO::openFile() {
	
	if (isInvalidArgument(fileName, mode)) {
		return;
	}

	if (this->getMode() == READ_MODE) {
		file.open(this->fileName, std::ios::in);
		return;
	}

	file.open(this->fileName, std::ios::out);
	return;
}

void FileIO::closeFile() {
	file.close();
}

bool FileIO::isOpen() {
	return file.is_open();
}
