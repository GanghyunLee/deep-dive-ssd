#include "gmock/gmock.h"
#include "Ssd.h"

using namespace testing;

class ReaderMock : public IReader {
public:
	MOCK_METHOD(void, read, (int), (override));
};

class WriterMock : public IWriter {
public:
	MOCK_METHOD(void, write, (int, std::string), (override));
};

class SSDFixture : public Test {
public:
	ReaderMock reader;
	WriterMock writer;
	SSD* ssd = new SSD(&reader, &writer);
};

TEST_F(SSDFixture, ReaderSuccess) {
	int index = 0;
	
	EXPECT_CALL(reader, read(index)).Times(1);

	ssd->read(index);
}

TEST_F(SSDFixture, ReaderFailedByIndex) {
	int index = 100;

	EXPECT_THROW(ssd->read(index), std::exception);
}

TEST_F(SSDFixture, WriterSuccess) {
	int index = 0;
	std::string value = "0x12345678";
	
	EXPECT_CALL(writer, write(index, value)).Times(1);

	ssd->write(index, value);
}

TEST_F(SSDFixture, WriterFailedByIndex) {
	int index = 100;
	std::string value = "0x12345678";

	EXPECT_THROW(ssd->write(index, value), std::exception);
}