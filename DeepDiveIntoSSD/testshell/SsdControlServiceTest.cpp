#include "gmock/gmock.h"
#include "SsdControlService.cpp"

using namespace testing;

TEST(SsdControlService, ReadTest) {
	SsdControlService service;
	SsdReadResult result;
	unsigned int data = 0;

	service.Write(0, 1);
	data = service.Read(0).data;
	EXPECT_EQ(data, 1);
}

TEST(SsdControlService, WriteTest) {
	SsdControlService service;
	SsdReadResult result;

	service.Write(0, 2);
	result = service.Read(0);
	EXPECT_EQ(result.data, 2);
}
TEST(SsdControlService, ExitTest) {
	SsdControlService service;
	bool result = false;

	result = service.Exit();
	EXPECT_EQ(true, result);
}

TEST(SsdControlService, FullReadTest) {
	SsdControlService service;
	SsdReadResult result;
	unsigned int data = 0;

	service.FullWrite(0);
	data = service.FullRead().data;
	EXPECT_EQ(0, data);
}

TEST(SsdControlService, FullWriteTest) {
	SsdControlService service;
	SsdReadResult result;
	unsigned int data = 0;

	service.FullWrite(0);
	data = service.FullRead().data;
	EXPECT_EQ(0, data);
}

TEST(SsdControlServicHelp, HelpTest) {
	SsdControlServicHelp help;
	bool result = false;

	result = help.Help();
	EXPECT_EQ(true, result);
}

TEST(SsdControlServiceTestScenario, TestScenario1) {
	SsdControlServiceTestScenario scenario1;
	bool result = false;

	result = scenario1.TestScenario_1();
	EXPECT_EQ(true, result);
}

TEST(SsdControlServiceTestScenario, TestScenario2) {
	SsdControlServiceTestScenario scenario1;
	bool result = false;

	result = scenario1.TestScenario_2();
	EXPECT_EQ(true, result);
}

TEST(SsdControlServiceTestScenario, TestScenario3) {
	SsdControlServiceTestScenario scenario1;
	bool result = false;

	result = scenario1.TestScenario_3();
	EXPECT_EQ(true, result);
}
