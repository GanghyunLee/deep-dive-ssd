#pragma once
#include <string>

#include "ISsdController.h"

class SsdController : public ISsdController
{
public:
	SsdWriteResult Write(int lba, unsigned int data) override;

private:
	std::string ExecuteCommand(const std::string& cmd);
	std::string ToUpperHex(unsigned int value);
	std::string ReadFileToString(const std::string& filename);
};

