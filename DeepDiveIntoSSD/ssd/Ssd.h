#pragma once

#include "ReaderWriter.h"
#include "ArgManager.h"
#include <iostream>
#include <iomanip>

class SSD {
public:
	SSD(IReader* reader, IWriter* writer, ArgManager* argManager) : m_reader{ reader }, m_writer{ writer }, m_argManager{argManager} {}
	
	void run(int argc, char* argv[]) {
		std::vector<std::string> commands = m_argManager->commandSplit(argc, argv);
		if (!m_argManager->isValid(commands))
			throw std::exception();

		Arg arg = m_argManager->makeStruct(commands);
		if (arg.RWflag) {
			write(arg.index, arg.value);
		}
		else {
			read(arg.index);
		}
	}
	
	void read(int index) {
		if (index < 0 || index > 99)
			throw std::exception();
		m_reader->read(index);
	}
	void write(int index, std::string value) {
		if (index < 0 || index > 99)
			throw std::exception();
		m_writer->write(index, value);
	}

	void initFile() {

		std::fstream dataFile("ssd_nand.txt", std::ios::out);
		
		for (int i = 0; i < 100; i++) {
			// 1. 정수 출력: 폭 2, 오른쪽 정렬, 공백 채움
			dataFile << std::setw(2) << std::right << i << " ";

			// 2. 16진수 출력: 폭 10, 0으로 채움, 소문자, 접두어 없음
			dataFile << std::setw(10) << std::setfill('0') << std::hex << std::nouppercase << 0 << std::endl;
		}

		dataFile.close();
	}

private:
	IReader* m_reader;
	IWriter* m_writer;
	ArgManager* m_argManager;
};