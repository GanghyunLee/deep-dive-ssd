#include "CommandBuffer.h"
#include <iostream>

bool CommandBuffer::checkDirectory() {
	return fileIO.checkDirectory();
}

void CommandBuffer::resetBuffer() {
	fileIO.removeFilesInDirectory();
	buffers = {};
	std::vector<std::string> initailBuffers = { "1_empty","2_empty", "3_empty", "4_empty", "5_empty" };
	for (const auto& bufferName : initailBuffers) {
		fileIO.createFile("buffer/" + bufferName);
		buffers.push_back(parseBufferNameToArg(bufferName));
	}
}

void CommandBuffer::createBuffer() {
	fileIO.createDirectory();
	resetBuffer();
}

void CommandBuffer::loadBuffer() {
	std::vector<std::string> bufferNames = fileIO.getFileNamesInDirectory();
	for (const auto& bufferName : bufferNames) {
		buffers.push_back(parseBufferNameToArg(bufferName));
	}
}

Arg CommandBuffer::parseBufferNameToArg(const std::string& fileName)
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

	Arg arg = argManager.makeStruct(args);

	return arg;
}

bool CommandBuffer::isBufferFull()
{
	if (buffers[4].commandType != EMPTY)
		return true;
	return false;
}

std::vector<Arg> CommandBuffer::getBuffer()
{
	return buffers;
}

std::string CommandBuffer::makeBufferNameFromArg(Arg arg, int index)
{
	char num = '0' + index;
	std::string type;
	if (arg.commandType == EMPTY) {
		type = "_empty";
		return num + type;
	}

	std::string idx = std::to_string(arg.index);
	if (arg.commandType == WRITE) {
		type = "_w_";
	}
	else {
		type = "_e_";
	}

	return num + type + idx + "_" + arg.value;
}

void CommandBuffer::updateBuffers(std::vector<Arg> ret) {
	fileIO.removeFilesInDirectory();
	int index = 0;
	for (const auto& buffer : ret) {
		buffers[index++] = buffer;
		std::string bufferName = makeBufferNameFromArg(buffer, index);
		fileIO.createFile("buffer/" + bufferName);
	}
}

int CommandBuffer::checkValueFromBuffer(int index)
{
	return algo.getStatus(index);
}

int CommandBuffer::fastRead(int index)
{
	int ret = 0;
	for (int i = buffers.size() - 1; i >= 0; i--) {
		if (buffers[i].commandType == EMPTY || buffers[i].commandType == ERASE)
			continue;
		if (buffers[i].index != index)
			continue;
		if (buffers[i].commandType == WRITE) {
			ret = std::stoul(buffers[i].value, nullptr, 16);
			break;
		}
	}
	return ret;
}

void CommandBuffer::pushBuffer(Arg arg)
{
	for (int i = 0; i < buffers.size(); i++) {
		if (buffers[i].commandType == EMPTY) {
			buffers[i] = arg;
			break;
		}
	}

	//for test.
	// algorithm 구현 되면 없애야함.
	{
		updateBuffers(buffers);
		return;
	}

	std::vector<Arg> returnByIgnore = algo.ignoreCommand(buffers);
	if (arg.commandType == WRITE) {
		updateBuffers(returnByIgnore);
		return;
	}

	std::vector<Arg> returnByMerge = algo.mergeErase(returnByIgnore);
	updateBuffers(returnByMerge);

	return;
}