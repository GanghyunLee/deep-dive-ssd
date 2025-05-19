#include "gmock/gmock.h"
#include <ostream>
#include "HelpCommand.h"
#include "HelpCommandMapper.h"

using namespace std;
using namespace testing;

class MockHelpCommand : public HelpCommand
{
public:
	~MockHelpCommand() override = default;

public:
	MOCK_METHOD(std::shared_ptr<IView>, Execute, (), (override));
};

class HelpCommandMapperTestFixture : public Test
{
public:
	~HelpCommandMapperTestFixture() override = default;

protected:
	void SetUp() override
	{
		mockHelpCommand = std::make_shared<MockHelpCommand>();
		helpCommandMapper = std::make_shared<HelpCommandMapper>(mockHelpCommand);
	}

public:
	std::shared_ptr<MockHelpCommand> mockHelpCommand = nullptr;
	std::shared_ptr<HelpCommandMapper> helpCommandMapper = nullptr;
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