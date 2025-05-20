#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "FileIO.h"
#include <filesystem>

bool FileIO::isInvalidArgument(const std::string& fileName, int mode) {

	if ((fileName == "ssd_nand.txt") || (fileName == "ssd_output.txt")) {
		return false;
	}

	if ((mode == READ_MODE) && (mode == WRITE_TRUNC_MODE) && (mode == WRITE_APPEND_MODE)) {
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

	if (this->getMode() == WRITE_APPEND_MODE) {
		file.open(this->fileName, std::ios::out | std::ios::app);
		return;
	}

	if (this->getMode() == WRITE_TRUNC_MODE) {
		file.open(this->fileName, std::ios::out | std::ios::trunc);
		return;
	}
}

void FileIO::closeFile() {
	file.close();
}

bool FileIO::isOpen() {
	return file.is_open();
}


std::string FileIO::readLine() {

	if (mode != READ_MODE) {
		throw std::exception("모드가 일치하지 않습니다.");
	}
	if (!isOpen()) {
		throw std::exception("파일이 열리지 않았습니다.");
	}

	std::string a;
	std::getline(file, a);

	if (a == EOF_STRING) {
		return EOF_STRING;
	}

	return a;
}

void FileIO::writeLine(const std::string& line) {

	if ((mode != WRITE_APPEND_MODE) && (mode != WRITE_TRUNC_MODE)) {
		throw std::exception("모드가 일치하지 않습니다.");
	}

	if (!isOpen()) {
		throw std::exception("파일이 열리지 않았습니다.");
	}

	file << line << std::endl;
	return;
}

bool FileIO::checkDirectory() {
	std::filesystem::path p("buffer");

	if (std::filesystem::exists(p))
		return true;
	return false;
}

void FileIO::createDirectory() {
	std::filesystem::path p("buffer");
	std::filesystem::create_directory(p);
}

void FileIO::createFile(const std::string& fileName) {
	std::ofstream file(fileName);
	file.close();
}

std::vector<std::string> FileIO::getFileNamesInDirectory() {
	std::vector<std::string> fileNames;
	std::filesystem::path p("buffer");

	for (const auto& entry : std::filesystem::directory_iterator(p)) {
		if (std::filesystem::is_regular_file(entry.status())) {
			fileNames.push_back(entry.path().filename().string());
		}
	}

	return fileNames;
}

void FileIO::removeFilesInDirectory()
{
	std::filesystem::path p("buffer");

	for (const auto& entry : std::filesystem::directory_iterator(p)) {
		if (std::filesystem::is_regular_file(entry.status())) {
			std::filesystem::remove(entry.path());
		}
	}
}