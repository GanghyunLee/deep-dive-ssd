#pragma once

#include <string>

class IReader {
public:
	virtual void read(int index) = 0;
};

class IWriter {
public:
	virtual void write(int index, std::string value) = 0;
};
