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

TEST_F(CommandBufferAlgorithmFixture, DISABLED_fastRead) {
	std::vector<Arg> buffer = {};
	std::string expected = {};
	Arg ret = cba.fastRead(buffer);

	//EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, CanMergeTest1) {
	CommandBufferAlgorithm cba;
	Arg a = { COMMAND_TYPE::ERASE, 10, "3" };
	Arg b = { COMMAND_TYPE::ERASE, 12, "3" };

	cba.mergeAble(a, b);
	EXPECT_TRUE(cba.mergeAble(a, b));
}

TEST(CommandBufferAlgorithm, CanMergeTest2) {
	CommandBufferAlgorithm cba;
	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "4" }, { COMMAND_TYPE::ERASE, 10, "4" }));
}

TEST(CommandBufferAlgorithm, CanMergeTest3) {
	CommandBufferAlgorithm cba;
	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "2" }, { COMMAND_TYPE::ERASE, 12, "2" }));
}

TEST(CommandBufferAlgorithm, CanMergeTest4) {
	CommandBufferAlgorithm cba;
	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "3" }, { COMMAND_TYPE::ERASE, 10, "3" }));
}

TEST(CommandBufferAlgorithm, CanMergeTest5) {
	CommandBufferAlgorithm cba;
	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "5" }, { COMMAND_TYPE::ERASE, 15, "5" }));
}

TEST(CommandBufferAlgorithm, CantMergeTestNotContinuous) {
	CommandBufferAlgorithm cba;
	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "1" }, { COMMAND_TYPE::ERASE, 12, "1" }));
}

TEST(CommandBufferAlgorithm, CantMergeTestNotContinuous2) {
	CommandBufferAlgorithm cba;
	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 5, "5" }, { COMMAND_TYPE::ERASE, 11, "1" }));
}

TEST(CommandBufferAlgorithm, CantMergeTestEraseSizeOverFlow) {
	CommandBufferAlgorithm cba;
	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 5, "8" }, { COMMAND_TYPE::ERASE, 11, "5" }));
}

TEST(CommandBufferAlgorithm, MergeTwoEraseOperationTest1) {
	CommandBufferAlgorithm cba;

	Arg merged = cba.mergeTwoCommand({ COMMAND_TYPE::ERASE, 10, "3" }, { COMMAND_TYPE::ERASE, 10, "3" });
	EXPECT_EQ(merged.commandType, COMMAND_TYPE::ERASE);
	EXPECT_EQ(merged.index, 10);
	EXPECT_EQ(merged.value, "3");
}

TEST(CommandBufferAlgorithm, MergeTwoEraseOperationTest2) {
	CommandBufferAlgorithm cba;

	Arg merged = cba.mergeTwoCommand({ COMMAND_TYPE::ERASE, 10, "5" }, { COMMAND_TYPE::ERASE, 15, "5" });
	EXPECT_EQ(merged.commandType, COMMAND_TYPE::ERASE);
	EXPECT_EQ(merged.index, 10);
	EXPECT_EQ(merged.value, "10");
}

TEST(CommandBufferAlgorithm, MergeTwoEraseOperationTest3) {
	CommandBufferAlgorithm cba;

	Arg merged = cba.mergeTwoCommand({ COMMAND_TYPE::ERASE, 10, "2" }, { COMMAND_TYPE::ERASE, 12, "2" });
	EXPECT_EQ(merged.commandType, COMMAND_TYPE::ERASE);
	EXPECT_EQ(merged.index, 10);
	EXPECT_EQ(merged.value, "4");
}