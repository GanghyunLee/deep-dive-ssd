#include "gmock/gmock.h"
#include "CommandBufferAlgorithm.h"

class CommandBufferAlgorithmFixture : public testing::Test {
public:
	void SetUp() override{

	}

	CommandBufferAlgorithm cba;
};

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand1) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{WRITE,10,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> expected = { {ERASE,11,"4"},{WRITE,10,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand2) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> expected = { {ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand3) {
	std::vector<Arg> buffer = { {ERASE,15,"5"},{ERASE,13,"10"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> expected = { {ERASE,13,"10"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand4) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,12,"0xABCD1234"},{WRITE,13,"0xABCD1234"},{ERASE,10,"5"}};
	std::vector<Arg> expected = { {ERASE,10,"5"},{0,},{0,},{0,},{0,}};
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand5) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{WRITE,11,"0xABCD1234"},{ERASE,10,"5"},{EMPTY,},{EMPTY,}};
	std::vector<Arg> expected = { {ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand6) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,}, };
	std::vector<Arg> expected = { {WRITE,10,"0xABCD1234"},{0,},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand7) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> expected = { {ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand8) {
	std::vector<Arg> buffer = { {ERASE,10,"4"},{WRITE,12,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,13,"0xABCD1234"} };
	std::vector<Arg> expected = { {WRITE,12,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,13,"0xABCD1234"},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand9) {
	std::vector<Arg> buffer = { {ERASE,10,"10"},{ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> expected = { {ERASE,10,"10"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}