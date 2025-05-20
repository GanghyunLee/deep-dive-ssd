#include "gmock/gmock.h"
#include "CommandBufferAlgorithm.h"

TEST(CommandBufferAlgorithm, ignoreCommand1) {
	std::vector<std::string> buffer = { "1_E_10_5", "2_W_10_0xABCD1234", "3_E_14_5", "4_empty", "5_emtpy" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_E_11_4", "2_W_10_0xABCD1234", "3_E_14_5", "4_empty", "5_emtpy" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand2) {
	std::vector<std::string> buffer = { "1_W_10_0xABCD1234", "2_E_10_5", "3_empty", "4_empty", "5_empty" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_E_10_5", "2_empty", "3_empty", "4_empty", "5_empty" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand3) {
	std::vector<std::string> buffer = { "1_E_15_5", "2_E_13_10", "3_empty", "4_empty", "5_empty" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_E_13_10", "2_empty", "3_empty", "4_empty", "5_empty" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand4) {
	std::vector<std::string> buffer = { "1_W_10_0xABCD1234", "2_W_11_0xABCD1234", "3_W_12_0xABCD1234", "4_W_13_0xABCD1234", "5_E_10_5" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_E_10_5", "2_empty", "3_empty", "4_empty", "5_empty" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand5) {
	std::vector<std::string> buffer = { "1_W_10_0xABCD1234", "2_E_10_5", "3_W_11_0xABCD1234", "4_E_10_5", "5_W_13_0xABCD1234" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_W_13_0xABCD1234", "2_empty", "3_empty", "4_empty", "5_empty" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand6) {
	std::vector<std::string> buffer = { "1_W_10_0xABCD1234", "2_W_10_0xABCD1234", "3_W_10_0xABCD1234", "4_W_10_0xABCD1234", "5_W_10_0xABCDABCD" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_W_10_0xABCDABCD", "2_empty", "3_empty", "4_empty", "5_empty" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, ignoreCommand7) {
	std::vector<std::string> buffer = { "1_E_10_5", "2_E_10_5", "3_E_10_5", "4_E_10_5", "5_E_10_5" };
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = { "1_E_10_5", "2_empty", "3_empty", "4_empty", "5_empty" };
	std::vector<std::string> ret = cba.ignoreCommand();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, mergeErase) {
	std::vector<std::string> buffer = {};
	CommandBufferAlgorithm cba{ buffer };
	std::vector<std::string> expected = {};
	std::vector<std::string> ret = cba.mergeErase();

	EXPECT_EQ(expected, ret);
}

TEST(CommandBufferAlgorithm, fastRead) {
	std::vector<std::string> buffer = {};
	CommandBufferAlgorithm cba{ buffer };
	std::string expected = {};
	std::string ret = cba.fastRead();

	EXPECT_EQ(expected, ret);
}
