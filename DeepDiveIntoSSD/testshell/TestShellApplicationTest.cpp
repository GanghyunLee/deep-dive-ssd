#include "ICommandMapper.h"
#include "TestShellApplication.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;

class MockCommandMapper : public ICommandMapper
{
public:
	MOCK_METHOD(bool, IsSupport, (const std::vector<std::string>&), (override));
	MOCK_METHOD(ICommand*, GenerateCommand, (const std::vector<std::string>&), (override));
};

class TestShellApplicationTestFixture : public Test
{
protected:
	void SetUp() override
	{
		sut = new TestShellApplication {
			std::vector<ICommandMapper*> {&mockCommandMapper},
			istream, ostream, false
		};
	}

	void TearDown() override
	{
		if (sut)
		{
			delete sut;
			sut = nullptr;
		}
	}
	
public:
	MockCommandMapper mockCommandMapper{};
	std::istringstream istream;
	std::ostringstream ostream;
	TestShellApplication* sut = nullptr;

	void EnqueueCommandWithExitCommand(const string& commandInput)
	{
		stringstream ss;
		ss << commandInput << endl << "exit";
		istream.str(ss.str());
		sut->Run();
	}
};

TEST_F(TestShellApplicationTestFixture, InvalidCommandMustPrintInvalidCommandError)
{
	EXPECT_CALL(mockCommandMapper, IsSupport(_))
		.Times(1)
		.WillRepeatedly(Return(false));

	EnqueueCommandWithExitCommand("INVALID_CMD");

	EXPECT_EQ(ostream.str(), "INVALID COMMAND\n");
}