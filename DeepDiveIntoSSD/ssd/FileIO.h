#pragma once
#include <fstream>
class FileIO {
public:
	const int READ_MODE = 1;
	const int WRITE_APPEND_MODE = 2;
	const int WRITE_TRUNC_MODE = 3;

	const std::string EOF_STRING = "";

	FileIO() = default;

	bool isInvalidArgument(const std::string& fileName, int mode);
	void setArgument(const std::string& fileName, int mode);
	int getMode() const;
	std::string getFileName() const;

	void openFile();
	void closeFile();
	bool isOpen();

	std::string readLine();
	void writeLine(const std::string&);


private:
	int mode;
	std::string fileName;
	std::fstream file;
};