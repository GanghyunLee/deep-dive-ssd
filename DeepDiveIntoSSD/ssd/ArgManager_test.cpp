#include "ArgManager.h"
#include "gmock/gmock.h"

TEST(ArgManager, commandSplit1) {
	ArgManager am;
	std::vector<std::string> argsExpect{ "R", "3" };
	char arg0[] = "R";
	char arg1[] = "3";

	char* input[] = { arg0,arg1 };

	EXPECT_EQ(argsExpect, am.commandSplit(2, input));
}

TEST(ArgManager, commandSplit2) {
	ArgManager am;
	std::vector<std::string> argsExpect{ "W", "3", "0x12345678"};
	char arg0[] = "W";
	char arg1[] = "3";
	char arg2[] = "0x12345678";

	char* input[] = { arg0,arg1,arg2 };

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST(ArgManager, commandSplit3) {
	ArgManager am;
	std::vector<std::string> argsExpect{ "R", "3", "0x12345678" };
	char arg0[] = "R";
	char arg1[] = "3";
	char arg2[] = "0x12345678";

	char* input[] = { arg0,arg1,arg2 };

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST(ArgManager, commandSplit4) {
	ArgManager am;
	std::vector<std::string> argsExpect{ "RW", "3", "0x12345678" };
	char arg0[] = "RW";
	char arg1[] = "3";
	char arg2[] = "0x12345678";

	char* input[] = { arg0,arg1,arg2 };

	EXPECT_EQ(argsExpect, am.commandSplit(3, input));
}

TEST(ArgManager, isValid1) {
	ArgManager am;
	std::vector<std::string> args{ "W", "3", "0x12345678" };

	EXPECT_EQ(true, am.isValid(args));
}

TEST(ArgManager, isValid2) {
	ArgManager am;
	std::vector<std::string> args{ "R", "3"};

	EXPECT_EQ(true, am.isValid(args));
}

TEST(ArgManager, isValid3) {
	ArgManager am;
	std::vector<std::string> args{ "R", "3", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST(ArgManager, isValid4) {
	ArgManager am;
	std::vector<std::string> args{ "RW", "3", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST(ArgManager, isValid5) {
	ArgManager am;
	std::vector<std::string> args{ "W", "103", "0x12345678" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST(ArgManager, isValid6) {
	ArgManager am;
	std::vector<std::string> args{ "W", "3", "0x123456788" };

	EXPECT_EQ(false, am.isValid(args));
}

TEST(ArgManager, DISABLED_makeStruct1) {
	ArgManager am;
	Arg argExpected = { true, 3, "0x12345678" };
	std::vector<std::string> args{ "W", "3", "0x12345678" };

	EXPECT_EQ(argExpected.index, am.makeStruct(args).index);
	EXPECT_EQ(argExpected.RWflag, am.makeStruct(args).RWflag);
	EXPECT_EQ(argExpected.value, am.makeStruct(args).value);
}

TEST(ArgManager, DISABLED_makeStruct2) {
	ArgManager am;
	Arg argExpected = { false, 3, "" };
	std::vector<std::string> args{ "R", "3" };

	EXPECT_EQ(argExpected.index, am.makeStruct(args).index);
	EXPECT_EQ(argExpected.RWflag, am.makeStruct(args).RWflag);
	EXPECT_EQ(argExpected.value, am.makeStruct(args).value);
}