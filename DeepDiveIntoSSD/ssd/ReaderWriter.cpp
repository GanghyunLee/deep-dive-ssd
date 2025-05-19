#include <string>
#include <iostream>
#include "ReaderWriter.h"
#include "FileIO.h"

int Reader::read(int index)  {

	fileIO = new FileIO();
	fileIO->setArgument("ssd_nand.txt", fileIO->READ_MODE);
	fileIO->openFile();

	// READ ALL
	while (true) {
		std::string line = fileIO->readLine();

		if (line == fileIO->EOF_STRING) {
			break;
		}
		
		// line parsing here. 
		std::cout << line << "\n";
	}

	// RETURN VALUE 
	return 0;
}

void Writer::write(int index, const std::string& value) {
	return;
}
