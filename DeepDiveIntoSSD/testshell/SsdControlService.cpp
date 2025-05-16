#include <iosfwd>
#include <string>
#include <sstream>
#include <iostream>
#include "SsdReadResult.h"

using namespace std;

class SsdControlService
{
public:
	SsdReadResult Read(int lba)
	{
		std::stringstream ss;
		unsigned int value;
		SsdReadResult result;

		ss << "ssd.exe R " << to_string(lba) << endl;
		system(ss.str().c_str());
		cin >> hex >> value;
		result.data = value;
		return SsdReadResult{};
	}
	void Write(int lba, unsigned int value) {
		stringstream ss;

		ss << "ssd.exe W" << to_string(lba) << " " << to_string(value) << endl;
		system(ss.str().c_str());
	}
};
