#include <iosfwd>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
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

		ss << "ssd.exe W " << to_string(lba) << " " << "0x" << hex << setw(8) << setfill('0') << value << endl;
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

class SsdControlServiceTestScenario {
public:
	bool TestScenario_1() {
		SsdControlService service;
		SsdReadResult result;
		unsigned int value = 1;
		int i, j, k;

		for (k = 0; k < 20; ++k) {
			for (i = 0; i < 5; ++i) {
				service.Write((k * 5) + i, value);
			}
			for (j = 0; j < 5; ++j) {
				result = service.Read((k * 5) + j);
				if (value != result.data) {
					return false;
				}
			}
			value += 1;
		}
		return true;
	}
	bool TestScenario_2() {
		SsdControlService service;
		SsdReadResult result;
		unsigned int value = 1;

		for (int i = 0; i < 30; ++i) {
			service.Write(4, value);
			service.Write(0, value);
			service.Write(3, value);
			service.Write(1, value);
			service.Write(2, value);

			result = service.Read(4);
			if (result.data != service.Read(0).data) {
				return false;
			}
			if (result.data != service.Read(3).data) {
				return false;
			}
			if (result.data != service.Read(1).data) {
				return false;
			}
			if (result.data != service.Read(2).data) {
				return false;
			}
		}
		return true;
	}
	bool TestScenario_3() {
		SsdControlService service;
		SsdReadResult result;
		unsigned int value = 1;

		for (int i = 0; i < 200; ++i) {
			std::srand(std::time(0));
			unsigned int value = std::rand();

			service.Write(0, value);
			service.Write(99, value);

			if (value != service.Read(0).data) {
				return false;
			}
			if (value != service.Read(99).data) {
				return false;
			}
		}
		return true;
	}
};