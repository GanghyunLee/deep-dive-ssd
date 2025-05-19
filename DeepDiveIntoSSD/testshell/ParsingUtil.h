#pragma once
#include <string>

class ParsingUtil
{
public:
	ParsingUtil() = delete;

public:
	static bool ContainsHexPrefix(const std::string& str);
	static unsigned int HexStringToDecimal(const std::string& hexStr);
};

