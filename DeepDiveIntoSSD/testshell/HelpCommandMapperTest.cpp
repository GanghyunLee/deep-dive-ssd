#include "gmock/gmock.h"
#include <ostream>
#include "HelpCommand.h"
#include "HelpCommandMapper.h"

using namespace std;
using namespace testing;

class MockHelpCommand : public HelpCommand
{
public:
	MockHelpCommand() : HelpCommand(nullptr) {}
	~MockHelpCommand() override = default;

public:
	MOCK_METHOD(IView*, Execute, (), (override));
};

class HelpCommandMapperTestFixture : public Test
{
public:
	~HelpCommandMapperTestFixture() override = default;

protected:
	void SetUp() override
	{
		mockHelpCommand = new MockHelpCommand();
		helpCommandMapper = new HelpCommandMapper(mockHelpCommand);
	}

	void TearDown() override
	{
		delete mockHelpCommand; mockHelpCommand = nullptr;
		delete helpCommandMapper; helpCommandMapper = nullptr;
	}

public:
	MockHelpCommand* mockHelpCommand = nullptr;
	HelpCommandMapper* helpCommandMapper = nullptr;
};

TEST_F(HelpCommandMapperTestFixture, HelpCommandMapperValidArgumentTest)
{
	std::vector<std::string> argument{ "help" };

	EXPECT_TRUE(helpCommandMapper->IsSupport(argument));
	EXPECT_EQ(helpCommandMapper->GenerateCommand(argument), mockHelpCommand);
}

TEST_F(HelpCommandMapperTestFixture, HelpCommandMapperValidArgumentButContainsUselessParameterTest)
{
	std::vector<std::string> argument{ "help", "useless param" };

	EXPECT_FALSE(helpCommandMapper->IsSupport(argument));
}

TEST_F(HelpCommandMapperTestFixture, HelpCommandMapperInvalidArgumentTest)
{
	std::vector<std::string> argument{ "adasfd" };

	EXPECT_FALSE(helpCommandMapper->IsSupport(argument));
}