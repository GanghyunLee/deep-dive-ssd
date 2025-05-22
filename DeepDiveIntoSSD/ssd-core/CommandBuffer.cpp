#include "CommandBuffer.h"
#include <iostream>

bool CommandBuffer::checkDirectory() {
	return fileIO.checkDirectory();
}

void CommandBuffer::resetBuffer() {
	fileIO.removeFilesInDirectory();
	buffer = {};
	std::vector<std::string> initialBuffer = { "1_empty","2_empty", "3_empty", "4_empty", "5_empty" };
	for (const auto& bufferName : initialBuffer) {
		fileIO.createFile("buffer/" + bufferName);
		buffer.push_back(parseBufferNameToCommand(bufferName));
	}
}

void CommandBuffer::createBuffer() {
	fileIO.createDirectory();
	resetBuffer();
}

void CommandBuffer::loadBuffer() {
	std::vector<std::string> bufferNames = fileIO.getFileNamesInDirectory();
	for (const auto& bufferName : bufferNames) {
		buffer.push_back(parseBufferNameToCommand(bufferName));
	}
}

Command CommandBuffer::parseBufferNameToCommand(const std::string& fileName)
{
	std::vector<std::string> args;
	std::string str = "";
	for (int i = 2; i < fileName.size(); i++) {
		if (fileName[i] == '_') {
			args.push_back(str);
			str = "";
			continue;
		}
		str += fileName[i];
	}
	args.push_back(str);

	Command command = argManager.makeCommand(args);

	return command;
}

bool CommandBuffer::isBufferFull()
{
	if (buffer[4].type != EMPTY)
		return true;
	return false;
}

std::vector<Command> CommandBuffer::getBuffer()
{
	return buffer;
}

std::string CommandBuffer::makeBufferNameFromCommand(Command command, int index)
{
	char num = '0' + index;
	std::string type;
	if (command.type == EMPTY) {
		type = "_empty";
		return num + type;
	}

	std::string idx = std::to_string(command.index);
	if (command.type == WRITE) {
		type = "_w_";
	}
	else {
		type = "_e_";
	}

	return num + type + idx + "_" + command.value;
}

void CommandBuffer::updateBuffers(std::vector<Command> ret) {
	fileIO.removeFilesInDirectory();
	int index = 0;
	for (const auto& command : ret) {
		buffer[index++] = command;
		std::string bufferName = makeBufferNameFromCommand(command, index);
		fileIO.createFile("buffer/" + bufferName);
	}
}

int CommandBuffer::checkBufferStatus(int index)
{
	int cmdCount = algo.getCommandCount(buffer);
	if (cmdCount == 0) {
		return CLEAN;
	}

	Command lastCmd = buffer[cmdCount -1];
	algo.getCurrentStatus(buffer);	

	if (lastCmd.type == ERASE) {
		algo.setStatusWithEraseCommand(lastCmd);
	}
	
	if (lastCmd.type == WRITE) {
		algo.setStatusWithWriteCommand(lastCmd);
	}

	return algo.getStatus(index);
}

int CommandBuffer::fastRead(int index)
{
	int ret = 0;
	for (int i = buffer.size() - 1; i >= 0; i--) {
		
		Command command = buffer[i];

		if (command.type == EMPTY || command.type == ERASE)
			continue;
		if (command.index != index)
			continue;
		if (command.type == WRITE) {
			ret = std::stoul(command.value, nullptr, 16);
			break;
		}
	}
	return ret;
}

void CommandBuffer::pushCommand(Command command)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i].type == EMPTY) {
			buffer[i] = command;
			break;
		}
	}

	std::vector<Command> returnByIgnore = algo.ignoreCommand(buffer);
	if (command.type == WRITE) {
		updateBuffers(returnByIgnore);
		return;
	}

	std::vector<Command> returnByMerge = algo.merge(returnByIgnore);
	updateBuffers(returnByMerge);

	return;
}