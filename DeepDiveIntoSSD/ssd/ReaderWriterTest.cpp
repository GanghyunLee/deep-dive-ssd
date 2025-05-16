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
	EXPECT_CALL(reader, read).Times(1);

	ssd->read(0);
}

TEST_F(SSDFixture, WriterSuccess) {
	EXPECT_CALL(writer, write).Times(1);

	ssd->write(0, "0x12345678");
}