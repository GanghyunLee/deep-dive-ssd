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
		memory->dumpError();
		return;
	}

	m_commandBuffer = new CommandBuffer();
	if (m_commandBuffer->checkDirectory()) {
		m_commandBuffer->loadBuffer();
	}
	else {
		m_commandBuffer->createBuffer();
	}

	Command arg = m_argManager->makeCommand(commands);
	if (arg.type == COMMAND_TYPE::READ) {
		int status = m_commandBuffer->checkBufferStatus(arg.index);
		if (status == STATUS::ERASED) {
			memory->dumpResult(arg.index, 0);
		}
		else if (status == STATUS::MODIFIED) {
			int modifiedValue = m_commandBuffer->fastRead(arg.index);
			memory->dumpResult(arg.index, modifiedValue);
		}
		else if (status == STATUS::CLEAN) {
			read(arg.index);
		}
		return;
	}
	
	if (arg.type == COMMAND_TYPE::FLUSH) {
		flushBuffers();
		return;
	}

	if (m_commandBuffer->isBufferFull()) {
		flushBuffers();
	}
	m_commandBuffer->pushBuffer(arg);
	memory->dumpSuccess();
	return;
}

void SSD::read(int index) {

	if (index < 0 || index > 99)
	{
		memory->dumpError();
		return;
	}

	memory->readOne(index);
}

void SSD::write(int index, std::string value) {

	if (index < 0 || index > 99)
	{
		memory->dumpError();
		return;
	}

	memory->readAll();
	memory->updateData(index, std::stoul(value, nullptr, 16));
	memory->dumpData();
	memory->dumpSuccess();
}

void SSD::erase(int index, std::string rangeString) {

	if (index < 0 || index > 99)
	{
		memory->dumpError();
		return;
	}

	unsigned int range = stoul(rangeString, nullptr, 10);
	if (range > 10)
	{
		memory->dumpError();
		return;
	}

	if (index + range > 100)
	{
		memory->dumpError();
		return;
	}

	if (range == 0)
	{
		//Do Nothing;
		memory->dumpSuccess();
		return;
	}

	memory->readAll();
	for (int dataIdx = index; dataIdx < index + range; dataIdx++) {
		memory->updateData(dataIdx, 0);
	}
	memory->dumpData();
	memory->dumpSuccess();

}

void SSD::flushBuffers()
{
	std::fstream file(INPUT_FILE, std::ios::in);
	if (!file.is_open()) {
		memory->dumpData();
	}
	file.close();
	std::vector<Command> buffer = m_commandBuffer->getBuffer();

	for (const auto& command : buffer) {
		switch (command.type) {
		case COMMAND_TYPE::WRITE:
			write(command.index, command.value);
			break;

		case COMMAND_TYPE::ERASE:
			erase(command.index, command.value);
			break;

		case COMMAND_TYPE::EMPTY:
			break;
		}
	}
	m_commandBuffer->resetBuffer();
	return;
}

void SSD::initNand()
{
	memory = memoryFactory.createFileMemoryForSSD();
	memory->init();
}
