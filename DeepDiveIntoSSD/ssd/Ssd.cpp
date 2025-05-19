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
		throw std::exception();

	Arg arg = m_argManager->makeStruct(commands);
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

	// read here , update output.txt  
	int value = m_reader->read(index);

}

void SSD::write(int index, std::string value) {
	if (index < 0 || index > 99)
	{
		dumpError();
		return;
	}

	readAllData();
	data[index] = std::stoi(value, nullptr, 16);
	dumpData();
	m_writer->write(index, std::stoi(value, nullptr, 16));

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

	std::fstream dataFile("ssd_nand.txt");

	for (int i = 0; i < 100; i++) {
		dataFile << std::dec << std::setfill('0') << std::setw(2) << i;
		dataFile << " ";
		dataFile << std::hex << std::setfill('0') << std::setw(10) << std::nouppercase << data[i];
		ss << std::hex << std::setfill('0') << std::setw(8) << std::nouppercase << data[i];
	}

	dataFile.close();
}

void SSD::dumpError() {

	std::fstream file("ssd_output.txt", std::ios::out | std::ios::trunc);
	file << "ERROR";
	file.close();
	return;
}