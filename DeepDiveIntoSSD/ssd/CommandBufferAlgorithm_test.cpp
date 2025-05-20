#include "gmock/gmock.h"
#include "CommandBufferAlgorithm.h"

TEST(CommandBufferAlgorithm, ignoreCommand1) {
	std::vector<Arg> buffer = { {3, 10, "5"}, {2, 10, "0xABCD1234"}, {3, 14, "5"}, {0,}, {0,} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {3, 11, "4"}, {2,10,"0xABCD1234"}, {3,14,"5"}, {0,}, {0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand2) {
	std::vector<Arg> buffer = { {2,10,"0xABCD1234"}, {3,10,"5"}, {0,}, {0,}, {0,} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {3,10,"5"}, {0,}, {0,}, {0,}, {0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand3) {
	std::vector<Arg> buffer = { {3,15,"5"}, {3,13,"10"}, {0,}, {0,}, {0,} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {3,13,"10"},{0,}, {0,}, {0,}, {0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand4) {
	std::vector<Arg> buffer = { {2,10,"0xABCD1234"}, {2,11,"0xABCD1234"}, {2,12,"0xABCD1234"}, {2,13,"0xABCD1234"}, {3,10,"5"} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {3,10,"5"}, {0,}, {0,}, {0,}, {0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand5) {
	std::vector<Arg> buffer = { {2,10,"0xABCD1234"}, {3,10,"5"}, {2,11,"0xABCD1234"}, {3,10,"5"}, {2,13,"0xABCD1234"} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {3,10,"5"}, {2,13,"0xABCD1234"}, {0,}, {0,}, {0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand6) {
	std::vector<Arg> buffer = { {2,10,"0xABCD1234"}, {2,10,"0xABCD1234"}, {2,10,"0xABCD1234"}, {2,10,"0xABCD1234"}, {2,10,"0xABCD1234"} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {2,10,"0xABCD1234"}, {0,}, {0,}, {0,}, {0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand7) {
	std::vector<Arg> buffer = { {3,10,"5"},{3,10,"5"},{3,10,"5"},{3,10,"5"},{3,10,"5"} };
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = { {3,10,"5"}, {0,},{0,},{0,},{0,} };
	std::vector<Arg> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, mergeErase) {
	std::vector<Arg> buffer = {};
	CommandBufferAlgorithm cba;
	std::vector<Arg> expected = {};
	std::vector<Arg> ret = cba.mergeErase(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, fastRead) {
	std::vector<Arg> buffer = {};
	CommandBufferAlgorithm cba;
	std::string expected = {};
	Arg ret = cba.fastRead(buffer);

	EXPECT_EQ(expected, ret);
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

TEST(CommandBufferAlgorithm, CantMergeTest1) {
	CommandBufferAlgorithm cba;
	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "1" }, { COMMAND_TYPE::ERASE, 12, "1" }));
}

TEST(CommandBufferAlgorithm, CantMergeTest2) {
	CommandBufferAlgorithm cba;
	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "3" }, { COMMAND_TYPE::ERASE, 10, "3" }));
}