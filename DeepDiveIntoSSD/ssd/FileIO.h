#pragma once
#include <fstream>

class FileIO {
public:
	const int READ_MODE = 1;
	const int WRITE_MODE = 2;

	FileIO() = default;
	void setArgument(const std::string& fileName, int mode);
	int getMode() const;
	std::string getFileName() const;

	void openFile();
	void closeFile();
	bool isOpen();

private:
	int mode;
	std::string fileName;
	std::fstream file;

};