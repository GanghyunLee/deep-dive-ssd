#include "gmock/gmock.h"
#include "Ssd.h"

using namespace testing;

class ReaderMock : public IReader {
public:
	MOCK_METHOD(void, read, (int), (override));
};

class WriterMock : public IWriter {
public:
	MOCK_METHOD(void, write, (int, const std::string&), (override));
};

class SSDFixture : public Test {
public:
	ReaderMock reader;
	WriterMock writer;
	ArgManager argManager;
	SSD* ssd = new SSD(&reader, &writer, &argManager);
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

TEST_F(SSDFixture, RunWrite) {
	char arg0[] = "W";
	char arg1[] = "3";
	char arg2[] = "0x12345678";
	char* input[] = { arg0,arg1,arg2 };

	EXPECT_CALL(writer, write).Times(1);

	ssd->run(3, input);
}

TEST_F(SSDFixture, RunRead) {
	char arg0[] = "R";
	char arg1[] = "3";
	char* input[] = { arg0,arg1 };

	EXPECT_CALL(reader, read).Times(1);

	ssd->run(2, input);
}

TEST_F(SSDFixture, RunInvalidCommandKeyword) {
	char arg0[] = "RW";
	char arg1[] = "3";
	char arg2[] = "0x12345678";
	char* input[] = { arg0,arg1,arg2 };

	EXPECT_THROW(ssd->run(3, input), std::exception);
}

TEST_F(SSDFixture, RunInvalidCommandRangeOut) {
	char arg0[] = "R";
	char arg1[] = "103";
	char* input[] = { arg0,arg1 };

	EXPECT_THROW(ssd->run(2, input), std::exception);
}

TEST_F(SSDFixture, RunInvalidCommandParameterCount) {
	char arg0[] = "R";
	char arg1[] = "3";
	char arg2[] = "0x12345678";
	char* input[] = { arg0,arg1,arg2 };

	EXPECT_THROW(ssd->run(3, input), std::exception);
}