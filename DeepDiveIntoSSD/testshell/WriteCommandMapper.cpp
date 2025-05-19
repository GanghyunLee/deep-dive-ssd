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
	// "0x"�� ���ڿ��� ���ԵǾ� �ִ��� üũ
	return str.find("0x") != std::string::npos;
}

unsigned int WriteCommandMapper::HexStringToDecimal(const std::string& hexStr)
{
	// "0x"�� ������ �̸� ����
	std::string cleanedStr = hexStr;

	// "0x"�� ���ڿ��� ó���� ������ ����
	if (cleanedStr.substr(0, 2) == "0x" || cleanedStr.substr(0, 2) == "0X") {
		cleanedStr = cleanedStr.substr(2);
	}

	// 16���� ���ڿ��� 10������ ��ȯ
	return  std::stoul(cleanedStr, nullptr, 16);
}
