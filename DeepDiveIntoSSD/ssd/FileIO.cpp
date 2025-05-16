#include <iostream>
#include <fstream>
#include <string>
#include "FileIO.h"

void FileIO::setArgument(const std::string& fileName, int mode) {
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
