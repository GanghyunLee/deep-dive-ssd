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

class Reader : public IReader {
public:
	void read(int index) override {
		return;
	}
};

class Writer : public IWriter {
public:
	void write(int index, std::string value) override {
		return;
	}
};
