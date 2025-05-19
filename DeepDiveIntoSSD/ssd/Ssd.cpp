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

	readAll();
	dumpResult(index, data[index]);

	// mock 
	m_reader->read(index);
}

void SSD::write(int index, std::string value) {
	
	if (index < 0 || index > 99)
	{
		dumpError();
		return;
	}

	readAll();
	updateData(index, std::stoul(value, nullptr, 16));
	dumpData();
	dumpSuccess();

	m_writer->write(index, std::stoul(value, nullptr, 16));

}

void SSD::updateData(int index, unsigned int value) {
	data[index] = value;
}

void SSD::readAll() {

	fileIO = new FileIO();
	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);
	fileIO->openFile();

	while (true) {

		std::string line = fileIO->readLine();
		
		if (line == fileIO->EOF_STRING) {
			break;
		}

		std::stringstream ss(line);
		int index;
		unsigned int value;
		ss >> std::dec >> index;
		ss >> std::hex >> value;

		data[index] = value;
	}
	
	fileIO->closeFile();
	delete fileIO;
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

void SSD::dumpResult(int index, unsigned int value) {
	std::fstream file(OUTPUT_FILE, std::ios::out | std::ios::trunc);
	file << "0x" << std::hex << std::setfill('0') << std::setw(8) << value;
	file.close();
}

void SSD::dumpSuccess() {
	fileIO = new FileIO();
	fileIO->setArgument(OUTPUT_FILE, fileIO->WRITE_TRUNC_MODE);
	fileIO->openFile();
	fileIO->writeLine("");
	fileIO->closeFile();
	return;
}