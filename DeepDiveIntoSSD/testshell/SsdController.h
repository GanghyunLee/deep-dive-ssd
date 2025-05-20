#pragma once
#include <string>

#include "ISsdController.h"

class SsdController : public ISsdController
{
public:
	SsdWriteResult Write(int lba, unsigned int data) override;
	SsdReadResult Read(int lba) override;
	SsdEraseResult Erase(int lba, int size) override;

private:
	std::string ExecuteCommand(const std::string& cmd);
	std::string ToUpperHex(unsigned int value);
	std::string ReadFileToString(const std::string& filename);
	unsigned int With0xPrefixHexStringToUInt(const std::string& hexString);

private:
	const std::string STR_SSD_EXE_FILE_NAME = "ssd.exe";
	const std::string STR_ERROR_STRING_FROM_SSD = "ERROR";
	const std::string STR_SSD_OUTPUT_TXT_FILE_NAME = "ssd_output.txt";
};

