#include "gmock/gmock.h"
#include "CommandBufferAlgorithm.h"

class CommandBufferAlgorithmFixture : public testing::Test {
public:
	void SetUp() override{

	}

	CommandBufferAlgorithm cba;
};

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand1) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{WRITE,10,"0xABCD1234"},{ERASE,14,"5"},{0,},{0,} };
	std::vector<Arg> expected = { {ERASE,11,"4"},{WRITE,10,"0xABCD1234"},{ERASE,14,"5"},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand2) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{ERASE,10,"5"},{0,},{0,},{0,} };
	std::vector<Arg> expected = { {ERASE,10,"5"},{0,},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand3) {
	std::vector<Arg> buffer = { {ERASE,15,"5"},{ERASE,13,"10"},{0,},{0,},{0,} };
	std::vector<Arg> expected = { {ERASE,13,"10"},{0,},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand4) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,12,"0xABCD1234"},{WRITE,13,"0xABCD1234"},{ERASE,10,"5"}};
	std::vector<Arg> expected = { {ERASE,10,"5"},{0,},{0,},{0,},{0,}};
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand5) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{ERASE,10,"5"},{WRITE,11,"0xABCD1234"},{ERASE,10,"5"},{WRITE,13,"0xABCD1234"}};
	std::vector<Arg> expected = { {ERASE,10,"5"},{WRITE,13,"0xABCD1234"},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand6) {
	std::vector<Arg> buffer = { {WRITE,10,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,10,"0xABCD1234"} };
	std::vector<Arg> expected = { {WRITE,10,"0xABCD1234"},{0,},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand7) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{ERASE,10,"5"},{ERASE,10,"5"},{ERASE,10,"5"},{ERASE,10,"5"} };
	std::vector<Arg> expected = { {ERASE,10,"5"},{0,},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_ignoreCommand8) {
	std::vector<Arg> buffer = { {ERASE,10,"4"},{WRITE,12,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,13,"0xABCD1234"} };
	std::vector<Arg> expected = { {WRITE,12,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{WRITE,13,"0xABCD1234"},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_mergeErase1) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{ERASE,15,"5"},{ERASE,20,"5"},{ERASE,25,"5"},{ERASE,30,"5"}};
	std::vector<Arg> expected = { {ERASE,10,"10"},{ERASE,20,"10"},{ERASE,30,"5"},{0,},{0,} };
	std::vector<Arg> ret = cba.mergeErase(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_mergeErase2) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{WRITE,12,"0xABCD1234"},{ERASE,15,"5"},{ERASE,20,"5"},{ERASE,25,"5"} };
	std::vector<Arg> expected = { {ERASE,10,"5"},{WRITE,12,"0xABCD1234"},{ERASE,15,"10"},{ERASE,25,"5"},{0,} };
	std::vector<Arg> ret = cba.mergeErase(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_mergeErase3) {
	std::vector<Arg> buffer = { {ERASE,10,"5"},{WRITE,12,"0xABCD1234"},{ERASE,15,"5"},{WRITE,17,"0xABCD1234"},{ERASE,20,"5"} };
	std::vector<Arg> expected = { {ERASE,10,"5"},{WRITE,12,"0xABCD1234"},{ERASE,15,"5"},{WRITE,17,"0xABCD1234"},{ERASE,20,"5"} };
	std::vector<Arg> ret = cba.mergeErase(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, DISABLED_fastRead) {
	std::vector<Arg> buffer = {};
	std::string expected = {};
	Arg ret = cba.fastRead(buffer);

	//EXPECT_EQ(expected, ret);
}
