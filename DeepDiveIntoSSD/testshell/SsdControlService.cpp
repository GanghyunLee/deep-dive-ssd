#include <iosfwd>
#include <string>
#include "SsdReadResult.h"
#include <sstream>

using namespace std;

class SsdControlService
{
public:

public:
	SsdReadResult Read(int lba)
	{
		std::stringstream ss;
		ss << "ssd.exe " << std::to_string(lba) << std::endl;
		system("ssd.exe ");
		return SsdReadResult{};
	}
};
