#include "gmock/gmock.h"
#include "Ssd.h"

using namespace testing;

class ReaderMock : public IReader {
public:
	MOCK_METHOD(int, read, (int), (override));
};

class WriterMock : public IWriter {
public:
	MOCK_METHOD(void, write, (int, const std::string &), (override));
};

class SSDFixture : public Test {
public:
	ReaderMock readerMock;
	WriterMock writerMock;
	ArgManager argManager;
	
	Reader reader;
	Writer writer;

	SSD* ssdMock = new SSD(&readerMock, &writerMock, &argManager);
	SSD* ssdReal = new SSD(&reader, &writer, &argManager);
};

TEST_F(SSDFixture, ReaderSuccess) {
	int index = 0;
	
	EXPECT_CALL(readerMock, read(index)).Times(1);

	ssdMock->read(index);
}

TEST_F(SSDFixture, ReaderFailedByIndex) {
	int index = 100;

	EXPECT_THROW(ssdMock->read(index), std::exception);
}

TEST_F(SSDFixture, WriterSuccess) {
	int index = 0;
	std::string value = "0x12345678";
	
	EXPECT_CALL(writerMock, write(index, value)).Times(1);

	ssdMock->write(index, value);
}

TEST_F(SSDFixture, WriterFailedByIndex) {
	int index = 100;
	std::string value = "0x12345678";

	EXPECT_THROW(ssdMock->write(index, value), std::exception);
}

TEST_F(SSDFixture, initSDSNANDTXTfile) {

	ssdReal->initData();

	std::fstream fp("ssd_nand.txt", std::ios::in);
	int lineNum = 0;
	std::string line;
	
	while (std::getline(fp, line)) {
		lineNum++;
	}

	EXPECT_EQ(lineNum, 100);
}

TEST_F(SSDFixture, readSSDNANDTextFile) {

	ssdReal->initData();
	ssdReal->read(0);

	std::fstream fp("ssd_output.txt", std::ios::in);
	std::string line;

	std::getline(fp, line);
	EXPECT_EQ("0x0000000000", line);
	
}