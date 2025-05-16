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

}

void FileIO::closeFile() {

}

bool FileIO::isOpen() {

	return true;
}
