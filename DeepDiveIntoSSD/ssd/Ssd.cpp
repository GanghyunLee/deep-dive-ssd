#include <sstream>
#include <iostream>
#include <iomanip>

#include "Ssd.h"
#include "ArgManager.h"


void SSD::run(int argc, char* argv[]) {
	std::vector<std::string> commands = m_argManager->commandSplit(argc, argv);

	if (commands.size() == 0)
		return;

	if (!m_argManager->isValid(commands))
	{
		dumpError();
		return;
	}

	m_commandBuffer = new CommandBuffer();
	if (m_commandBuffer->checkDirectory()) {
		m_commandBuffer->loadBuffer();
	}
	else {
		m_commandBuffer->createBuffer();
	}

	Arg arg = m_argManager->makeStruct(commands);
	if (arg.commandType == COMMAND_TYPE::READ) {
		// do read
		//read(arg.index);
		return;
	}

	if (m_commandBuffer->isBufferFull()) {
		std::fstream file(INPUT_FILE, std::ios::in);
		if (!file.is_open()) {
			dumpData();
		}
		file.close();
		std::vector<Arg> buffers = m_commandBuffer->getBuffer();

		for (const auto& buffer : buffers) {
			switch (buffer.commandType) {
			case COMMAND_TYPE::WRITE:
				write(buffer.index, buffer.value);
				break;

			case COMMAND_TYPE::ERASE:
				erase(buffer.index, buffer.value);
				break;
			}
		}
		m_commandBuffer->resetBuffer();
	}

	m_commandBuffer->pushBuffer(arg);
}

void SSD::read(int index) {

	if (index < 0 || index > 99)
	{
		dumpError();
		return;
	}

	readAll();
	dumpResult(index, data[index]);
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
}

void SSD::erase(int index, std::string rangeString) {

	if (index < 0 || index > 99)
	{
		dumpError();
		return;
	}

	unsigned int range = stoul(rangeString, nullptr, 10);
	if (range > 10)
	{
		dumpError();
		return;
	}

	if (index + range > 100)
	{
		dumpError();
		return;
	}

	if (range == 0)
	{
		//Do Nothing;
		dumpSuccess();
		return;
	}

	readAll();
	for (int dataIdx = index; dataIdx < index + range; dataIdx++) {
		updateData(dataIdx, 0);
	}
	dumpData();
	dumpSuccess();

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
