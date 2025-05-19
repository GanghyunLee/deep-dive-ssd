#include "WriteCommandMapper.h"

#include "WriteCommand.h"

bool WriteCommandMapper::IsSupport(const std::vector<std::string>& userInputCommand)
{
	if (userInputCommand.size() != 3)
		return false;

	return userInputCommand[0] == "write";
}

std::shared_ptr<ICommand> WriteCommandMapper::GenerateCommand(const std::vector<std::string>& userInputCommand)
{
	int lba = std::stoi(userInputCommand[1]);
	if (false == ContainsHexPrefix(userInputCommand[2]))
		throw std::exception{ "INVALID ARGUMENT" };

	unsigned int data = HexStringToDecimal(userInputCommand[2]);
	return _writeCommandFactory(lba, data);
}

bool WriteCommandMapper::ContainsHexPrefix(const std::string& str)
{
	// "0x"가 문자열에 포함되어 있는지 체크
	return str.find("0x") != std::string::npos;
}

unsigned int WriteCommandMapper::HexStringToDecimal(const std::string& hexStr)
{
	// "0x"가 있으면 이를 제거
	std::string cleanedStr = hexStr;

	// "0x"가 문자열의 처음에 있으면 제거
	if (cleanedStr.substr(0, 2) == "0x" || cleanedStr.substr(0, 2) == "0X") {
		cleanedStr = cleanedStr.substr(2);
	}

	// 16진수 문자열을 10진수로 변환
	return  std::stoul(cleanedStr, nullptr, 16);
}
