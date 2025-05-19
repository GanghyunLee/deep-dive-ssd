#include "Ssd.h"
#include "ReaderWriter.h"
#include "ArgManager.h"

#include <iostream>
#include <iomanip>

void SSD::run(int argc, char* argv[]) {
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

void SSD::read(int index) {
	if (index < 0 || index > 99)
		throw std::exception();
	m_reader->read(index);
}

void SSD::write(int index, std::string value) {
	if (index < 0 || index > 99)
		throw std::exception();
	m_writer->write(index, value);
}

void SSD::initFile() {

	std::fstream dataFile("ssd_nand.txt");

	for (int i = 0; i < 100; i++) {
		dataFile << std::dec << std::setfill('0') << std::setw(2) << i;

		dataFile << " ";

		// 16진수: 폭 10, 0 채움, 소문자
		dataFile << std::hex << std::setfill('0') << std::setw(10) << std::nouppercase << 0;

		// 다음 줄
		dataFile << std::endl;
	}
	dataFile.close();
}
