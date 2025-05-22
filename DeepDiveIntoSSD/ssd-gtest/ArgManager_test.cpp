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
	char cArgs[3][20] = { 0 };
	int READ = 1;
	int WRITE = 2;
	int ERASE = 3;

	int INDEX = 3;

	void makeInput(std::vector<std::string> args) {
		for (int i = 0; i < args.size(); i++) {
			strcpy_s(cArgs[i], args[i].c_str());
			input[i] = cArgs[i];
		}
	}
};

TEST_F(ArgManagerFixture, commandSplit1) {
	argsExpect = { "R", "3"};
	makeInput({ "R", "3" });

	EXPECT_EQ(argsExpect, am.commandSplit(2, input));
}

TEST_F(ArgManagerFixture, commandSplit2) {
	argsExpect = { "W", "3", "0x12345678" };
	makeInput({ "W", "3", "0x12345678" });

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST_F(ArgManagerFixture, commandSplit3) {
	argsExpect = { "R", "3", "0x12345678" };
	makeInput({ "R", "3", "0x12345678" });

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST_F(ArgManagerFixture, commandSplit4) {
	argsExpect = { "RW", "3", "0x12345678" };
	makeInput({ "RW", "3", "0x12345678" });

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

TEST_F(ArgManagerFixture, isValid11) {
	std::vector<std::string> args{ "r", "2" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid12) {
	std::vector<std::string> args{ "w", "2", "0xabcdef", "123123", "agfef"};

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid13) {
	std::vector<std::string> args{ "R", "2", "0xabcdef01" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid14) {
	std::vector<std::string> args{ "W", "2", "0x0000abcd" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid15) {
	std::vector<std::string> args{ "W", "2" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid16) {
	std::vector<std::string> args{ "W", "acefs" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid17) {
	std::vector<std::string> args{ "W", "2", "qsefdse"};

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid18) {
	std::vector<std::string> args;

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid19) {
	std::vector<std::string> args{ "W" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid20) {
	std::vector<std::string> args{ "W", "3", "0x"};

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid21) {
	std::vector<std::string> args{ "", "", "" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid22) {
	std::vector<std::string> args{ "3", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid23) {
	std::vector<std::string> args{ "W", "3", "0x-2345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST_F(ArgManagerFixture, isValid24) {
	std::vector<std::string> args{ "W", "3", "0x-+*/" };

	EXPECT_EQ(false, am.isValid(args));
}


TEST_F(ArgManagerFixture, isValid25) {
	std::vector<std::string> args{ "E", "10", "2" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST_F(ArgManagerFixture, makeStruct1) {
	Command argExpected = { WRITE, INDEX, "0x12345678" };
	Command argsResult = am.makeCommand({ "W", "3", "0x12345678" });

	EXPECT_EQ(argExpected, argsResult);
}

TEST_F(ArgManagerFixture, makeStruct2) {
	Command argExpected = { READ, INDEX, "" };
	Command argsResult = am.makeCommand({ "R", "3" });

	EXPECT_EQ(argExpected, argsResult);
}

TEST_F(ArgManagerFixture, makeStruct3) {
	Command argExpected = { WRITE, INDEX, "0x0000abcd" };
	Command argsResult = am.makeCommand({ "W", "3", "0xabcd"});

	EXPECT_EQ(argExpected, argsResult);
}

TEST_F(ArgManagerFixture, fullTest) {
	Command argExpected = { WRITE, INDEX, "0x000A5678" };
	makeInput({ "W", "3", "0xa5678" });
	std::vector<std::string> args = am.commandSplit(3, input);
	am.isValid(args);

	Command argsResult = am.makeCommand(args);

	EXPECT_EQ(argExpected, argsResult);
}