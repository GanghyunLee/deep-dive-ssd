#include "IoC.h"
#include "TestShellApplication.h"
#include "gmock/gmock.h"
using namespace std;
using namespace testing;

class TestShellApplicationTestFixture : public Test
{
protected:
	void SetUp() override
	{
		testShellApplication = new TestShellApplication(ioc, istream, ostream, false);
	}

public:
	IoC ioc;
	std::istringstream istream;
	std::ostringstream ostream;

	TestShellApplication* testShellApplication = nullptr;

	void InitAndExecuteCommand(const string& commandInput)
	{
		stringstream ss;
		ss << commandInput << endl << "exit";
		istream.str(ss.str());
	}
};

TEST_F(TestShellApplicationTestFixture, InvalidCommandMustPrintInvalidCommandError)
{
	InitAndExecuteCommand("INVALID_CMD");

	testShellApplication->Run();
	EXPECT_EQ(ostream.str(), "INVALID COMMAND\n");
}