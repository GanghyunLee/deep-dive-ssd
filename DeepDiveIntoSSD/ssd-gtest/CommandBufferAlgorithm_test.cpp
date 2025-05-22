#include "gmock/gmock.h"
#include "CommandBufferAlgorithm.h"

class CommandBufferAlgorithmFixture : public testing::Test {
public:
	void SetUp() override {

	}

	CommandBufferAlgorithm cba;
};

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand1) {
	std::vector<Command> buffer = { {ERASE,10,"5"},{WRITE,10,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,11,"4"},{WRITE,10,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand2) {
	std::vector<Command> buffer = { {WRITE,10,"0xABCD1234"},{ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand3) {
	std::vector<Command> buffer = { {ERASE,15,"5"},{ERASE,13,"10"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,13,"10"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand4) {
	std::vector<Command> buffer = { {WRITE,10,"0xABCD1234"},{WRITE,11,"0xABCD1234"},{WRITE,12,"0xABCD1234"},{WRITE,13,"0xABCD1234"},{ERASE,10,"5"}};
	std::vector<Command> expected = { {ERASE,10,"5"},{0,},{0,},{0,},{0,}};
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand5) {
	std::vector<Command> buffer = { {ERASE,10,"5"},{WRITE,11,"0xABCD1234"},{ERASE,10,"5"},{EMPTY,},{EMPTY,}};
	std::vector<Command> expected = { {ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand6) {
	std::vector<Command> buffer = { {WRITE,10,"0xABCD1234"},{WRITE,10,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,}, };
	std::vector<Command> expected = { {WRITE,10,"0xABCD1234"},{0,},{0,},{0,},{0,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand7) {
	std::vector<Command> buffer = { {ERASE,0,"5"},{ERASE,0,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,0,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand8) {
	std::vector<Command> buffer = { {ERASE,95,"5"},{ERASE,95,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,95,"5"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand9) {
	std::vector<Command> buffer = { {ERASE,10,"10"},{ERASE,10,"5"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,10,"10"},{EMPTY,},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, ignoreCommand10) {
	std::vector<Command> buffer = { {ERASE,10,"5"},{WRITE,14,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> expected = { {ERASE,10,"4"},{WRITE,14,"0xABCD1234"},{EMPTY,},{EMPTY,},{EMPTY,} };
	std::vector<Command> ret = cba.ignoreCommand(buffer);

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, CanMergeTest1) {
	CommandBufferAlgorithm cba;
	std::vector<Command> buffer = { {ERASE,10,"3"},{ERASE,12,"3"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 12, "3" });

	Command a = { COMMAND_TYPE::ERASE, 10, "3" };
	Command b = { COMMAND_TYPE::ERASE, 12, "3" };

	cba.mergeAble(a, b);
	EXPECT_TRUE(cba.mergeAble(a, b));
}

TEST(CommandBufferAlgorithm, CanMergeTest2) {
	CommandBufferAlgorithm cba;
	
	std::vector<Command> buffer = { {ERASE,10,"3"},{ERASE,10,"4"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 10, "4" });

	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "4" }, { COMMAND_TYPE::ERASE, 10, "4" }));
}

TEST(CommandBufferAlgorithm, CanMergeTest3) {
	CommandBufferAlgorithm cba;
	std::vector<Command> buffer = { {ERASE,10,"2"},{ERASE,12,"2"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 12, "2" });

	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "2" }, { COMMAND_TYPE::ERASE, 12, "2" }));
}

TEST(CommandBufferAlgorithm, CanMergeTest4) {
	CommandBufferAlgorithm cba;

	std::vector<Command> buffer = { {ERASE,10,"3"},{ERASE,10,"3"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 10, "3" });


	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "3" }, { COMMAND_TYPE::ERASE, 10, "3" }));
}

TEST(CommandBufferAlgorithm, CanMergeTest5) {
	CommandBufferAlgorithm cba;

	std::vector<Command> buffer = { {ERASE,10,"5"},{ERASE,15,"5"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 15, "5" });

	EXPECT_TRUE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "5" }, { COMMAND_TYPE::ERASE, 15, "5" }));
}

TEST(CommandBufferAlgorithm, CantMergeTestNotContinuous) {
	CommandBufferAlgorithm cba;

	std::vector<Command> buffer = { {ERASE,10,"1"},{ERASE,12,"1"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 12, "1" });

	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 10, "1" }, { COMMAND_TYPE::ERASE, 12, "1" }));
}

TEST(CommandBufferAlgorithm, CantMergeTestNotContinuous2) {
	CommandBufferAlgorithm cba;

	std::vector<Command> buffer = { {ERASE,5,"5"},{ERASE,11,"1"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 11, "1" });

	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 5, "5" }, { COMMAND_TYPE::ERASE, 11, "1" }));
}

TEST(CommandBufferAlgorithm, CantMergeTestEraseSizeOverFlow) {
	CommandBufferAlgorithm cba;

	std::vector<Command> buffer = { {ERASE,5,"8"},{ERASE,11,"5"},{0,}, {0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 11, "5" });

	EXPECT_FALSE(cba.mergeAble({ COMMAND_TYPE::ERASE, 5, "8" }, { COMMAND_TYPE::ERASE, 11, "5" }));
}

TEST(CommandBufferAlgorithm, MergeTwoEraseOperationTest1) {
	CommandBufferAlgorithm cba;

	Command merged = cba.mergeTwoCommand({ COMMAND_TYPE::ERASE, 10, "3" }, { COMMAND_TYPE::ERASE, 10, "3" });
	EXPECT_EQ(merged.type, COMMAND_TYPE::ERASE);
	EXPECT_EQ(merged.index, 10);
	EXPECT_EQ(merged.value, "3");
}

TEST(CommandBufferAlgorithm, MergeTwoEraseOperationTest2) {
	CommandBufferAlgorithm cba;

	Command merged = cba.mergeTwoCommand({ COMMAND_TYPE::ERASE, 10, "5" }, { COMMAND_TYPE::ERASE, 15, "5" });
	EXPECT_EQ(merged.type, COMMAND_TYPE::ERASE);
	EXPECT_EQ(merged.index, 10);
	EXPECT_EQ(merged.value, "10");
}

TEST(CommandBufferAlgorithm, MergeTwoEraseOperationTest3) {
	CommandBufferAlgorithm cba;

	Command merged = cba.mergeTwoCommand({ COMMAND_TYPE::ERASE, 10, "2" }, { COMMAND_TYPE::ERASE, 12, "2" });
	EXPECT_EQ(merged.type, COMMAND_TYPE::ERASE);
	EXPECT_EQ(merged.index, 10);
	EXPECT_EQ(merged.value, "4");
}

TEST_F(CommandBufferAlgorithmFixture, mergeTest1) {
	std::vector<Command> buffer = { {ERASE,10,"5"},{ ERASE,15,"5" },{0,},{0,},{0,} };
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 15, "5" });
	std::vector<Command> expected = { {ERASE,10,"10"},{0,},{0,},{0,},{0,} };
	
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, mergeTest2) {
	std::vector<Command> buffer = { {WRITE,10,"0xABCD1234"},
								{WRITE,11,"0xABCD1234"},
								{WRITE,12,"0xABCD1234"},
								{ERASE,8, "5"},
								{ERASE,10, "5"} };

	std::vector<Command> expected = {{WRITE,10,"0xABCD1234"},
								{WRITE,11,"0xABCD1234"},
								{WRITE,12,"0xABCD1234"},
								{ERASE,8, "7"},
								{0,} };

	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 10, "5" });
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, mergeTest3) {
	std::vector<Command> buffer = { {ERASE,10,"10"},{ERASE, 10, "5"},{0,},{0,},{0,} };
	std::vector<Command> expected = { {ERASE,10,"10"},{0,},{0,},{0,},{0,} };

	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 10, "5" });
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, mergeTest4) {
	std::vector<Command> buffer = { {ERASE,10,"10"}, {WRITE, 40, "0xABCD1234"}, {ERASE, 11, "5"},{0,}, { 0, } };
	std::vector<Command> expected = { {WRITE, 40, "0xABCD1234"}, {ERASE,10, "10"}, { 0, }, { 0, }, { 0, } };
	
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 11, "5" });
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, mergeTestNothingHappened0) {

	// NOTHING HAPPENED

	std::vector<Command> buffer = { {ERASE,10,"5"},{WRITE,12,"0xABCD1234"},{ERASE,15,"5"},{0,},{0,} };
	
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 15, "5" });
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(ret, buffer);
}

TEST_F(CommandBufferAlgorithmFixture, mergeTestNothingHappened1) {
	std::vector<Command> buffer = { {ERASE,10,"3"},{WRITE,12,"0xABCD1234"},{ERASE,15,"5"},{0,},{0,} };
	std::vector<Command> expected = { {ERASE, 10, "3"},{WRITE,12,"0xABCD1234" }, {ERASE, 15,"5"}, {0,},{0,} };
	
	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 15, "5" });
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, mergeTestNothingHappened2) {

	// CAUTION (only for test)
	// CAN'T HAPPENED
	std::vector<Command> buffer = { {WRITE,12,"0xABCD1234"},{ERASE,10,"10"},{ERASE, 20, "5"}, {0,},{0,} };
	std::vector<Command> expected = { {WRITE,12,"0xABCD1234"},{ERASE,10,"10"},{ERASE, 20, "5"},{0,},{0,} };

	cba.getCurrentStatus(buffer);
	cba.setStatusWithEraseCommand({ ERASE, 20, "5" });
	std::vector<Command> ret = cba.merge(buffer);

	EXPECT_EQ(expected, ret);
}

TEST_F(CommandBufferAlgorithmFixture, commandCountTest) {

	std::vector<Command> buffer1 = { {WRITE,12,"0xABCD1234"},{ERASE,10,"10"},{ERASE, 20, "5"}, {0,},{0,} };
	std::vector<Command> buffer2 = { {WRITE,12,"0xABCD1234"},{ERASE,10,"10"}, {0, },{0,},{0,} };
	std::vector<Command> buffer3 = { {WRITE,12,"0xABCD1234"},{0,}, {0,},{0,},{0,} };
	std::vector<Command> buffer4 = { {0,},{0,}, {0,},{0,},{0,} };
	std::vector<Command> buffer5 = { {WRITE,12,"0xABCD1234"},{ERASE,10,"10"},{ERASE, 20, "5"}, {ERASE, 20, "5"},{ERASE, 20, "5"} };
	EXPECT_EQ(cba.getCommandCount(buffer1), 3);
	EXPECT_EQ(cba.getCommandCount(buffer2), 2);
	EXPECT_EQ(cba.getCommandCount(buffer3), 1);
	EXPECT_EQ(cba.getCommandCount(buffer4), 0);
	EXPECT_EQ(cba.getCommandCount(buffer5), 5);

}