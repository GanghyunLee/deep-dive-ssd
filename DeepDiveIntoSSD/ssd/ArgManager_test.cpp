#include "ArgManager.h"
#include "gmock/gmock.h"

class ArgManagerFixture : public testing::Test {
protected:
	void SetUp() override {
		argsExpect.clear();
	}
public:
	ArgManager am;
	std::vector<std::string> argsExpect;
	char* input[3];
	char cArg0[20] = { 0 };
	char cArg1[20] = { 0 };
	char cArg2[20] = { 0 };
	bool READ = false;
	bool WRITE = true;
	int INDEX = 3;

	void makeInput(std::string arg0, std::string arg1, std::string arg2 = "") {
		strcpy_s(cArg0, arg0.c_str());
		strcpy_s(cArg1, arg1.c_str());
		input[0] = cArg0;
		input[1] = cArg1;
		
		if (arg2 != "") {
			strcpy_s(cArg2, arg2.c_str());
			input[2] = cArg2;
		}
	}
};

TEST_F(ArgManagerFixture, commandSplit1) {
	argsExpect = { "R", "3"};
	makeInput("R", "3");

	EXPECT_EQ(argsExpect, am.commandSplit(2, input));
}

TEST_F(ArgManagerFixture, commandSplit2) {
	argsExpect = { "W", "3", "0x12345678" };
	makeInput("W", "3", "0x12345678");

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST_F(ArgManagerFixture, commandSplit3) {
	argsExpect = { "R", "3", "0x12345678" };
	makeInput("R", "3", "0x12345678");

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST_F(ArgManagerFixture, commandSplit4) {
	argsExpect = { "RW", "3", "0x12345678" };
	makeInput("RW", "3", "0x12345678");

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST_F(ArgManagerFixture, isValid1) {
	std::vector<std::string> args{ "W", "3", "0x12345678" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid2) {
	std::vector<std::string> args{ "R", "3"};

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid3) {
	std::vector<std::string> args{ "R", "3", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid4) {
	std::vector<std::string> args{ "RW", "3", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid5) {
	std::vector<std::string> args{ "W", "103", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid6) {
	std::vector<std::string> args{ "W", "3", "0x123456788" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid7) {
	std::vector<std::string> args{ "W", "3", "0x1234abcd" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid8) {
	std::vector<std::string> args{ "W", "3", "0x1234ABCD" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid9) {
	std::vector<std::string> args{ "W", "3", "0x1234KKkk" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid10) {
	std::vector<std::string> args{ "w", "3", "0x1234abCD" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isVali11) {
	std::vector<std::string> args{ "r", "2" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isVali12) {
	std::vector<std::string> args{ "w", "2", "0xabcdef", "123123", "agfef"};

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isVali13) {
	std::vector<std::string> args{ "R", "2", "0xabcdef01" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isVali14) {
	std::vector<std::string> args{ "W", "2", "0x0000abcd" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isVali15) {
	std::vector<std::string> args{ "W", "2" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, makeStruct1) {
	Arg argExpected = { WRITE, INDEX, "0x12345678" };
	Arg argsResult = am.makeStruct({ "W", "3", "0x12345678" });

	EXPECT_EQ(argExpected.index, argsResult.index);
	EXPECT_EQ(argExpected.isWrite, argsResult.isWrite);
	EXPECT_EQ(argExpected.value, argsResult.value);
}

TEST_F(ArgManagerFixture, makeStruct2) {
	Arg argExpected = { READ, INDEX, "" };
	Arg argsResult = am.makeStruct({ "R", "3" });

	EXPECT_EQ(argExpected.index, argsResult.index);
	EXPECT_EQ(argExpected.isWrite, argsResult.isWrite);
	EXPECT_EQ(argExpected.value, argsResult.value);
}

TEST_F(ArgManagerFixture, makeStruct3) {
	Arg argExpected = { WRITE, INDEX, "0x0000abcd" };
	Arg argsResult = am.makeStruct({ "W", "3", "0xabcd"});

	EXPECT_EQ(argExpected.index, argsResult.index);
	EXPECT_EQ(argExpected.isWrite, argsResult.isWrite);
	EXPECT_EQ(argExpected.value, argsResult.value);
}

TEST_F(ArgManagerFixture, fullTest) {
	Arg argExpected = { WRITE, INDEX, "0x000A5678" };
	makeInput("W", "3", "0xa5678");
	std::vector<std::string> args = am.commandSplit(3, input);
	am.isValid(args);

	Arg argsResult = am.makeStruct(args);

	EXPECT_EQ(argExpected.index, argsResult.index);
	EXPECT_EQ(argExpected.isWrite, argsResult.isWrite);
	EXPECT_EQ(argExpected.value, argsResult.value);
}