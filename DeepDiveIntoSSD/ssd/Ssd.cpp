#include "Ssd.h"
#include "ReaderWriter.h"
#include "ArgManager.h"

#include <sstream>
#include <iostream>
#include <iomanip>

void SSD::run(int argc, char* argv[]) {
	std::vector<std::string> commands = m_argManager->commandSplit(argc, argv);
	
	if (commands.size() == 0)
		return;
	
	if (!m_argManager->isValid(commands))
	{
		dumpError();
		return;
	}

	Arg arg = m_argManager->makeStruct(commands);

	std::fstream file(INPUT_FILE, std::ios::in);
	if (!file.is_open()) {
		dumpData();
	}
	file.close();


	if (arg.isWrite) {
		write(arg.index, arg.value);
	}
	else {
		read(arg.index);
	}
}

void SSD::read(int index) {

	if (index < 0 || index > 99)
	{
		dumpError();
		return;
	}

	readAllData();
	int value = m_reader->read(index);

}

void SSD::write(int index, std::string value) {
	
	if (index < 0 || index > 99)
	{
		dumpError();
		return;
	}

	readAllData();
	data[index] = std::stoul(value, nullptr, 16);
	dumpData();

	m_writer->write(index, std::stoul(value, nullptr, 16));
	fileIO = new FileIO();
	fileIO->setArgument(OUTPUT_FILE, fileIO->WRITE_TRUNC_MODE);
	fileIO->openFile();
	fileIO->writeLine("");
	fileIO->closeFile();
	delete fileIO;
}

void SSD::readAllData() {

	std::fstream dataFile("ssd_nand.txt", std::ios::in);
	std::string line;
	while (std::getline(dataFile, line)) {
		std::stringstream ss(line);
		
		int index, value;
		ss >> std::dec >> index;
		ss >> std::hex >> value;

		data[index] = value;
	}
	
	dataFile.close();
}

void SSD::dumpData() {

	fileIO = new FileIO();
	fileIO->setArgument(INPUT_FILE, fileIO->WRITE_TRUNC_MODE);
	fileIO->openFile();

	for (int i = 0; i < 100; i++) {
		std::stringstream ss;
		ss << std::dec << std::setfill('0') << std::setw(2) << i;
		ss << " 0x";
		ss << std::hex << std::setfill('0') << std::setw(8) << std::nouppercase << data[i];
	
		fileIO->writeLine(ss.str());
	}

	fileIO->closeFile();
	delete fileIO;

	return;
}

void SSD::dumpError() {

	fileIO = new FileIO();
	fileIO->setArgument(OUTPUT_FILE, fileIO->WRITE_TRUNC_MODE);
	fileIO->openFile();
	fileIO->writeLine("ERROR");
	fileIO->closeFile();
	return;

}