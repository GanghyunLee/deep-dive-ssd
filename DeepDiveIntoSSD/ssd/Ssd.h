#pragma once

#include "ReaderWriter.h"

class SSD {
public:
	SSD(IReader* reader, IWriter* writer) : m_reader{ reader }, m_writer{ writer } {}
	void read(int index) {
		if (index < 0 || index > 99)
			throw std::exception();
		m_reader->read(index);
	}
	void write(int index, std::string value) {
		if (index < 0 || index > 99)
			throw std::exception();
		m_writer->write(index, value);
	}
private:
	IReader* m_reader;
	IWriter* m_writer;
};