#include "ICommand.h"
#include "ICommandMapper.h"
#include "InMemoryLogger.h"
#include "TestShellApplication.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;

class MockCommandMapper : public ICommandMapper
{
public:
	~MockCommandMapper() override = default;

public:
	MOCK_METHOD(bool, IsSupport, (const std::vector<std::string>&), (override));
	MOCK_METHOD(std::shared_ptr<ICommand>, GenerateCommand, (const std::vector<std::string>&), (override));
};

class MockCommand : public ICommand
{
public:
	~MockCommand() override = default;

public:
	MOCK_METHOD(std::shared_ptr<IView>, Execute, (), (override));
};

class MockView : public IView
{
public:
	~MockView() override = default;

public:
	MOCK_METHOD(void, Render, (std::shared_ptr<ILogger>&), (override));
};

class TestShellApplicationTestFixture : public Test
{
protected:
	void SetUp() override
	{
		mockCommandMapper = std::make_shared<MockCommandMapper>();

		sut = std::make_shared<TestShellApplication>(
			std::vector<std::shared_ptr<ICommandMapper>> {mockCommandMapper},
			istream, logger, false
		);
	}
	
public:
	// Create This object only if it is required.
	shared_ptr<MockCommand> mockCommand = nullptr;
	shared_ptr<MockView> mockView = nullptr;

	std::shared_ptr<MockCommandMapper> mockCommandMapper;
	std::istringstream istream;
	std::ostringstream ostream;
	std::shared_ptr<ILogger> logger = std::make_shared<InMemoryLogger>(ostream);
	std::shared_ptr<TestShellApplication> sut = nullptr;

	void EnqueueCommandWithExitCommand(const string& commandInput)
	{
		stringstream ss;
		ss << commandInput << endl << "exit";
		istream.str(ss.str());
		sut->Run(1, nullptr);
	}

	const std::string STR_DUMMY_COMMAND = "DUMMY";
};

TEST_F(TestShellApplicationTestFixture, InvalidCommandMustPrintInvalidCommandError)
{
	EXPECT_CALL(*mockCommandMapper, IsSupport(_))
		.Times(1)
		.WillRepeatedly(Return(false));

	EXPECT_CALL(*mockCommandMapper, GenerateCommand(_))
		.Times(0);

	EnqueueCommandWithExitCommand(STR_DUMMY_COMMAND);

	EXPECT_EQ(ostream.str(), "INVALID COMMAND\n");
}

TEST_F(TestShellApplicationTestFixture, SupportedCommandMustGenerateValidCommand)
{
	mockCommand = std::make_shared<MockCommand>();

	EXPECT_CALL(*mockCommandMapper, IsSupport(_))
		.Times(1)
		.WillRepeatedly(Return(true));

	EXPECT_CALL(*mockCommandMapper, GenerateCommand(_))
		.Times(1)
		.WillRepeatedly(Return(mockCommand));

	EXPECT_CALL(*mockCommand, Execute)
		.Times(1)
		.WillRepeatedly(Return(nullptr));

	EnqueueCommandWithExitCommand(STR_DUMMY_COMMAND);

	EXPECT_EQ(ostream.str(), "\n");
}

TEST_F(TestShellApplicationTestFixture, CommandWhichHasAViewMustGenerateValidCommandAndRender)
{
	mockCommand = std::make_shared<MockCommand>();
	mockView = std::make_shared<MockView>();

	EXPECT_CALL(*mockCommandMapper, IsSupport(_))
		.Times(1)
		.WillRepeatedly(Return(true));

	EXPECT_CALL(*mockCommandMapper, GenerateCommand(_))
		.Times(1)
		.WillRepeatedly(Return(mockCommand));

	EXPECT_CALL(*mockCommand, Execute)
		.Times(1)
		.WillRepeatedly(Return(mockView));

	EXPECT_CALL(*mockView, Render(_))
		.Times(1);

	EnqueueCommandWithExitCommand(STR_DUMMY_COMMAND);

	EXPECT_EQ(ostream.str(), "\n");
}