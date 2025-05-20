#include "ParsingUtil.h"

bool ParsingUtil::ContainsHexPrefix(const std::string& str)
{
	// "0x"가 문자열에 포함되어 있는지 체크
	return str.find("0x") != std::string::npos;
}

unsigned int ParsingUtil::HexStringToDecimal(const std::string& hexStr)
{
	// "0x"가 있으면 이를 제거
	std::string cleanedStr = hexStr;

	// "0x"가 문자열의 처음에 있으면 제거
	if (cleanedStr.substr(0, 2) == "0x" || cleanedStr.substr(0, 2) == "0X") {
		cleanedStr = cleanedStr.substr(2);
	}
	for (char c : cleanedStr) {
		if (!std::isxdigit(static_cast<unsigned char>(c))) {
			throw std::exception{ "INVALID ARGUMENT" };
		}
	}
	// 16진수 문자열을 10진수로 변환
	return  std::stoul(cleanedStr, nullptr, 16);
}

int ParsingUtil::ConvertStringToOnlyPlusIntegerOrElseThrow(const std::string& str, bool isZeroOkay)
{
	int value = std::stoi(str);
	if (value < 0)
		throw std::exception{"Value is lower than 0"};

	if (isZeroOkay == false && value == 0)
		throw std::exception{ "Value is 0" };

	return value;
}
