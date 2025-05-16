#pragma once

#include "ReaderWriter.h"

class SSD {
public:
	SSD(IReader* reader, IWriter* writer) : m_reader{ reader }, m_writer{ writer } {}
	void read(int index) {
		m_reader->read(index);
	}
	void write(int index, std::string value) {
		m_writer->write(index, value);
	}
private:
	IReader* m_reader;
	IWriter* m_writer;
};