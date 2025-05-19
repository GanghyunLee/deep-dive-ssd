// #include <iosfwd>
// #include <string>
// #include <sstream>
// #include <iostream>
// #include <iomanip>
// #include "SsdReadResult.h"
//
// using namespace std;
//
// class SsdControlService
// {
// public:
// 	SsdReadResult Read(int lba)
// 	{
// 		std::stringstream ss;
// 		unsigned int value;
// 		SsdReadResult result;
//
// 		ss << "ssd.exe R " << to_string(lba) << endl;
// #ifdef _DEBUG
// 		cout << ss.str() << endl;
// 		value = ssd_value;
// #else
// 		system(ss.str().c_str());
// 		cin >> hex >> value;
// #endif
// 		result.data = value;
// 		cout << result.data << ", " << value << endl;
// 		return result;
// 	}
// 	void Write(int lba, unsigned int value) {
// 		stringstream ss;
//
// 		ss << "ssd.exe W " << to_string(lba) << " " << "0x" << hex << setw(8) << setfill('0') << value << endl;
// #ifdef _DEBUG
// 		cout << ss.str() << endl;
// 		ssd_value = value;
// #else
// 		system(ss.str().c_str());
// #endif
// 	}
// 	bool Exit() {
// 		std::stringstream ss{ "exit" };
// #ifdef _DEBUG
// 		cout << ss.str() << endl;
// #else
// 		system(ss.str().c_str());
// #endif
// 		return true;
// 	}
// 	SsdReadResult FullRead()
// 	{
// 		std::stringstream ss;
// 		unsigned int value;
// 		SsdReadResult result;
//
// 		for (int i = 0; i < 100; ++i) {
// 			ss << "ssd.exe R " << to_string(i) << endl;
// #ifdef _DEBUG
// 			cout << ss.str() << endl;
// 			value = ssd_value;
// #else
// 			system(ss.str().c_str());
// 			cin >> hex >> value;
// #endif
// 			result.data = value;
// 			return SsdReadResult{};
// 		}
// 	}
// 	void FullWrite(unsigned int value) {
// 		stringstream ss;
//
// 		for (int i = 0; i < 100; ++i) {
// 			ss << "ssd.exe W " << to_string(i) << " " << to_string(value) << endl;
// #ifdef _DEBUG
// 			cout << ss.str() << endl;
// 			ssd_value = value;
// #else
// 			system(ss.str().c_str());
// #endif
// 		}
// 	}
// private:
// 	unsigned int ssd_value = 0;
// };
//
// class SsdControlServicHelp {
// public:
// 	bool Help() {
// 		cout << "Team : DD(DeepDive)" << endl;
// 		cout << "writer : 이강현(팀장), 권격민, 김민석, 이문형, 이재규" << endl;
// 		cout << "write : ssd.exe W lba address" << endl;
// 		cout << "read : ssd.exe R address" << endl;
// 		cout << "fullwrite : ssd.exe fullwrite 0xABCDFFFF" << endl;
// 		cout << "fullread : ssd.exe fullread 0xABCDFFFF" << endl;
// 		return true;
// 	}
// };
//
// class SsdControlServiceTestScenario {
// public:
// 	bool TestScenario_1() {
// 		SsdControlService service;
// 		SsdReadResult result;
// 		unsigned int value = 1;
// 		int i, j, k;
//
// 		for (k = 0; k < 20; ++k) {
// 			for (i = 0; i < 5; ++i) {
// 				service.Write((k * 5) + i, value);
// 			}
// 			for (j = 0; j < 5; ++j) {
// 				result = service.Read((k * 5) + j);
// 				if (value != result.data) {
// 					return false;
// 				}
// 			}
// 			value += 1;
// 		}
// 		return true;
// 	}
// 	bool TestScenario_2() {
// 		SsdControlService service;
// 		SsdReadResult result;
// 		unsigned int value = 1;
//
// 		for (int i = 0; i < 30; ++i) {
// 			service.Write(4, value);
// 			service.Write(0, value);
// 			service.Write(3, value);
// 			service.Write(1, value);
// 			service.Write(2, value);
//
// 			result = service.Read(4);
// 			if (result.data != service.Read(0).data) {
// 				return false;
// 			}
// 			if (result.data != service.Read(3).data) {
// 				return false;
// 			}
// 			if (result.data != service.Read(1).data) {
// 				return false;
// 			}
// 			if (result.data != service.Read(2).data) {
// 				return false;
// 			}
// 		}
// 		return true;
// 	}
// 	bool TestScenario_3() {
// 		SsdControlService service;
// 		SsdReadResult result;
// 		unsigned int value = 1;
//
// 		for (int i = 0; i < 200; ++i) {
// 			std::srand(std::time(0));
// 			unsigned int value = std::rand();
//
// 			service.Write(0, value);
// 			service.Write(99, value);
//
// 			if (value != service.Read(0).data) {
// 				return false;
// 			}
// 			if (value != service.Read(99).data) {
// 				return false;
// 			}
// 		}
// 		return true;
// 	}
// };