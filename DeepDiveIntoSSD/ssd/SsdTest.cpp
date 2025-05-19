#include "gmock/gmock.h"
#include "Ssd.h"

class MainFixture : public testing::Test {
public:
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD* ssd = new SSD(&reader, &writer, &argManager);
};

TEST_F(MainFixture, Write) {
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD ssd(&reader, &writer, &argManager);

	char arg0[] = "W";
	char arg1[] = "3";
	char arg2[] = "0x12345678";
	char* input[] = { arg0,arg1,arg2 };

	ssd.run(3, input);
}

TEST_F(MainFixture, Read) {
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD ssd(&reader, &writer, &argManager);

	char arg0[] = "R";
	char arg1[] = "3";
	char* input[] = { arg0,arg1 };

	ssd.run(2, input);
}

TEST_F(MainFixture, InvalidCommandKeyword) {
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD ssd(&reader, &writer, &argManager);

	char arg0[] = "RW";
	char arg1[] = "3";
	char arg2[] = "0x12345678";
	char* input[] = { arg0,arg1,arg2 };

	EXPECT_THROW(ssd.run(3, input), std::exception);
}

TEST_F(MainFixture, InvalidCommandRangeOut) {
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD ssd(&reader, &writer, &argManager);

	char arg0[] = "R";
	char arg1[] = "103";
	char* input[] = { arg0,arg1 };

	EXPECT_THROW(ssd.run(2, input), std::exception);
}

TEST_F(MainFixture, InvalidCommandParameterCount) {
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD ssd(&reader, &writer, &argManager);

	char arg0[] = "R";
	char arg1[] = "3";
	char arg2[] = "0x12345678";
	char* input[] = { arg0,arg1,arg2 };

	EXPECT_THROW(ssd.run(3, input), std::exception);
}