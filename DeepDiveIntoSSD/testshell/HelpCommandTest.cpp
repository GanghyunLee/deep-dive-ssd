#include "HelpView.h"
#include "ICommandMapper.h"
#include "gmock/gmock.h"
#include <ostream>

#include "HelpCommand.h"

using namespace std;
using namespace testing;

class MockHelpView : public HelpView
{
public:
	~MockHelpView() override = default;

public:
	MOCK_METHOD(void, Render, (std::ostream&), (override));
};

class HelpCommandTestFixture : public Test
{
public:
	~HelpCommandTestFixture() override = default;

protected:
	void SetUp() override
	{
		mockHelpView = new MockHelpView();
		helpCommand = new HelpCommand(mockHelpView);
	}

	void TearDown() override
	{
		delete helpCommand; helpCommand = nullptr;
		delete mockHelpView; mockHelpView = nullptr;
	}

public:
	MockHelpView* mockHelpView = nullptr;
	HelpCommand* helpCommand = nullptr;
};

TEST_F(HelpCommandTestFixture, HelpCommandMustGenerateHelpView)
{
	EXPECT_EQ(helpCommand->Execute(), mockHelpView);
}