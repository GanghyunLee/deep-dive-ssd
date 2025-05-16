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

		ss << "ssd.exe W " << to_string(lba) << " " << to_string(value) << endl;
		system(ss.str().c_str());
	}
	void Exit() {
		std::stringstream ss{ "exit" };
		system(ss.str().c_str());
	}
	SsdReadResult FullRead()
	{
		std::stringstream ss;
		unsigned int value;
		SsdReadResult result;

		for (int i = 0; i < 100; ++i) {
			ss << "ssd.exe R " << to_string(i) << endl;
			system(ss.str().c_str());
			cin >> hex >> value;
			result.data = value;
			return SsdReadResult{};
		}
	}
	void FullWrite(unsigned int value) {
		stringstream ss;

		for (int i = 0; i < 100; ++i) {
			ss << "ssd.exe W " << to_string(i) << " " << to_string(value) << endl;
			system(ss.str().c_str());
		}
	}
};

class SsdControlServicHelp {
public:
	void Help() {
		cout << "Team : DD(DeepDive)" << endl;
		cout << "Writer : ÀÌ°­Çö, ±Ç°Ý¹Î, ±è¹Î¼®, ÀÌ¹®Çü, ÀÌÀç±Ô" << endl;
		cout << "write : ssd.exe W lba address" << endl;
		cout << "read : ssd.exe R address" << endl;
		cout << "ssd.exe fullwrite : ssd.exe fullwrite 0xABCDFFFF" << endl;
		cout << "ssd.exe fullread : ssd.exe fullread 0xABCDFFFF" << endl;
	}
};
