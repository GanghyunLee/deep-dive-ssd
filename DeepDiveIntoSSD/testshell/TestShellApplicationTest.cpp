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
		testShellApplication = new TestShellApplication(ioc, istream, ostream);
	}

public:
	IoC ioc;
	std::istringstream istream;
	std::ostringstream ostream;

	TestShellApplication* testShellApplication = nullptr;
};

TEST_F(TestShellApplicationTestFixture, InvalidCommandMustReturnInvalidCommandError)
{
	istream.str("INVALID_CMD");
	istream.str("exit");
	testShellApplication->Run();
	EXPECT_EQ(ostream.str(), "INVALID COMMAND");
}