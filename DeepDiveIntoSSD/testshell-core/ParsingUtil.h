#pragma once
#include <string>
#include <vector>

class ParsingUtil
{
public:
	ParsingUtil() = delete;

public:
	static bool ContainsHexPrefix(const std::string& str);
	static unsigned int HexStringToDecimal(const std::string& hexStr);
	static int ConvertStringToOnlyPlusIntegerOrElseThrow(const std::string& str, bool isZeroOkay);
	static std::vector<std::string> ArgvToVector(int argc, char* argv[]);
	static std::string ToLowerString(const std::string& str);
};

