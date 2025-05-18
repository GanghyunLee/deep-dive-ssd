#include "gmock/gmock.h"
#include "FileIO.h"

class FileIOFixture : public testing::Test {

public:
	const std::string OUTPUT_FILE = "sdd_output.txt";
	const std::string INPUT_FILE = "sdd_nand.txt";
	const std::string INVALID_FILE_NAME = "sdd_output234.txt";

protected:
	void SetUp() override {
	}

	void TearDown() override {
	}
};

TEST_F(FileIOFixture, GetArgumentForFileIO) {

	FileIO* fileIO = new FileIO();
	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);

	EXPECT_EQ(fileIO->getFileName(), INPUT_FILE);
	EXPECT_EQ(fileIO->getMode(), fileIO->READ_MODE);

}

TEST_F(FileIOFixture, FileOpenSuccess) {

	FileIO* fileIO = new FileIO();

	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);
	fileIO->openFile();

	EXPECT_TRUE(fileIO->isOpen());
}

TEST_F(FileIOFixture, MakeFileForHandlingNotFoundFileError) {

	// NOT IMPLEMENTED 

}

TEST_F(FileIOFixture, FileOpenFailedByInvalidName) {

	FileIO* fileIO = new FileIO();
	EXPECT_TRUE(fileIO->isInvalidArgument(INVALID_FILE_NAME, fileIO->READ_MODE));
	
	fileIO->setArgument(INVALID_FILE_NAME, fileIO->READ_MODE);
	fileIO->openFile();

	EXPECT_FALSE(fileIO->isOpen());

}

TEST_F(FileIOFixture, FileOpenFailedByNotArgumentSetting) {

	FileIO* fileIO = new FileIO();
	
	fileIO->openFile();
	
	EXPECT_FALSE(fileIO->isOpen());
}

TEST_F(FileIOFixture, FileClose) {

	FileIO* fileIO = new FileIO();

	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);
	fileIO->openFile();
	EXPECT_TRUE(fileIO->isOpen());

	fileIO->closeFile();
	EXPECT_FALSE(fileIO->isOpen());

}

TEST_F(FileIOFixture, readOneLine) {

	FileIO* fileIO = new FileIO();

	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);
	fileIO->openFile();
	std::string line = fileIO->readLine();
	fileIO->closeFile();

	EXPECT_EQ("DeepDiveSSD", line);
}

TEST_F(FileIOFixture, readWithoutOpenedFile) {

	FileIO* fileIO = new FileIO();

	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);

	try {
		fileIO->readLine();
		FAIL();
	}
	catch(std::exception &ex){
		EXPECT_THAT(std::string{ ex.what() }, testing::Eq("파일이 열리지 않았습니다."));
	}
}

TEST_F(FileIOFixture, readWithWriteModeFileIO) {

	FileIO* fileIO = new FileIO();

	fileIO->setArgument(INPUT_FILE, fileIO->WRITE_MODE);
	fileIO->openFile();

	try {
		fileIO->readLine();
		FAIL();
	}
	catch (std::exception& ex) {
		EXPECT_THAT(std::string{ ex.what() }, testing::Eq("모드가 일치하지 않습니다."));
	}

	fileIO->closeFile();

}

TEST_F(FileIOFixture, writeWithoutOpenedFile) {

	FileIO* fileIO = new FileIO();
	const std::string DUMMY_STRING = "DEEPDIVE SSD TEST STRING";
	fileIO->setArgument(INPUT_FILE, fileIO->WRITE_MODE);

	try {
		fileIO->writeLine(DUMMY_STRING);
		FAIL();
	}
	catch (std::exception& ex) {
		EXPECT_THAT(std::string{ ex.what() }, testing::Eq("파일이 열리지 않았습니다."));
	}
}

TEST_F(FileIOFixture, writeWithReadModeFileIO) {

	FileIO* fileIO = new FileIO();
	const std::string DUMMY_STRING = "DEEPDIVE SSD TEST STRING";
	fileIO->setArgument(INPUT_FILE, fileIO->READ_MODE);
	fileIO->openFile();

	try {
		fileIO->writeLine(DUMMY_STRING);
		FAIL();
	}
	catch (std::exception& ex) {
		EXPECT_THAT(std::string{ ex.what() }, testing::Eq("모드가 일치하지 않습니다."));
	}

	fileIO->closeFile();

}