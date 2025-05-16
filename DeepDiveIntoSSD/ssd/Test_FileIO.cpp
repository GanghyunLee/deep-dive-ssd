#include "gmock/gmock.h"
#include "FileIO.h"

TEST(FileIO, GetArgumentForFileIO) {

	FileIO* fileIO = new FileIO();
	const std::string fileName = "sdd_nand.txt";
	int mode = fileIO->READ_MODE;

	fileIO->setArgument(fileName, mode);

	EXPECT_EQ(fileIO->getFileName(), fileName);
	EXPECT_EQ(fileIO->getMode(), mode);

}

TEST(FileIO, FileOpenSuccess) {

	FileIO* fileIO = new FileIO();
	const std::string fileName = "sdd_nand.txt";
	int mode = fileIO->READ_MODE;

	fileIO->setArgument(fileName, mode);
	fileIO->openFile();

	EXPECT_TRUE(fileIO->isOpen());
}

TEST(FileIO, MakeFileForHandlingNotFoundFileError) {


}

TEST(FileIO, FileOpenFailedByInvalidName) {


}

TEST(FileIO, FileOpenFailedByNotArgumentSetting) {


}
