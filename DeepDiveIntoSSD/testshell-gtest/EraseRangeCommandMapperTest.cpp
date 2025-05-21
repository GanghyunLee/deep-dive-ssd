#include "gmock/gmock.h"
#include <ostream>
#include <memory>
#include "EraseRangeCommand.h"
#include "EraseRangeCommandMapper.h"

using namespace std;
using namespace testing;

class MockEraseRangeCommand : public EraseRangeCommand
{
public:
	MockEraseRangeCommand(int startLba, int endLba) : EraseRangeCommand(nullptr, startLba, endLba) {}
	~MockEraseRangeCommand() override = default;

public:
	MOCK_METHOD(std::shared_ptr<IView>, Execute, (), (override));
};

class EraseRangeCommandMapperTestFixture : public Test
{
public:
	~EraseRangeCommandMapperTestFixture() override = default;

public:
	void SetUp() override
	{
		eraseRangeCommandMapper = std::make_shared<EraseRangeCommandMapper>([&](int startLba, int endLba)
			{
				return make_shared<MockEraseRangeCommand>(startLba, endLba);
			});
	}

public:
	std::shared_ptr<EraseRangeCommandMapper> eraseRangeCommandMapper = nullptr;
};

TEST_F(EraseRangeCommandMapperTestFixture, ValidArgumentTestWithStartLbaIsGreaterThanEndLba)
{
	std::vector<std::string> validArgument{ "erase_range", "99", "0" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	shared_ptr<EraseRangeCommand> cmd = dynamic_pointer_cast<EraseRangeCommand>(eraseRangeCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetStartLba(), 0);
	EXPECT_EQ(cmd->GetEndLba(), 99);
}

TEST_F(EraseRangeCommandMapperTestFixture, ValidArgumentTestWithNormalCase)
{
	std::vector<std::string> validArgument{ "erase_range", "4", "8" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	shared_ptr<EraseRangeCommand> cmd = dynamic_pointer_cast<EraseRangeCommand>(eraseRangeCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetStartLba(), 4);
	EXPECT_EQ(cmd->GetEndLba(), 8);
}

TEST_F(EraseRangeCommandMapperTestFixture, InvalidArgumentWithMinusStartLba)
{
	std::vector<std::string> validArgument{ "erase_range", "-4", "10" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	EXPECT_THROW(eraseRangeCommandMapper->GenerateCommand(validArgument), std::exception);
}

TEST_F(EraseRangeCommandMapperTestFixture, InvalidArgumentWithMinusEndLba)
{
	std::vector<std::string> validArgument{ "erase_range", "14", "-86" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	EXPECT_THROW(eraseRangeCommandMapper->GenerateCommand(validArgument), std::exception);
}


TEST_F(EraseRangeCommandMapperTestFixture, InvalidArgumentWithBiggerStartLba)
{
	std::vector<std::string> validArgument{ "erase_range", "99999999", "4" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	EXPECT_THROW(eraseRangeCommandMapper->GenerateCommand(validArgument), std::exception);
}

TEST_F(EraseRangeCommandMapperTestFixture, InvalidArgumentWithMinusBiggerStartLba)
{
	std::vector<std::string> validArgument{ "erase_range", "-999999", "2" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	EXPECT_THROW(eraseRangeCommandMapper->GenerateCommand(validArgument), std::exception);
}

TEST_F(EraseRangeCommandMapperTestFixture, InvalidArgumentWithMinusStartLbaAndMinusEndLba)
{
	std::vector<std::string> validArgument{ "erase_range", "-27", "-86" };
	EXPECT_TRUE(eraseRangeCommandMapper->IsSupport(validArgument));

	EXPECT_THROW(eraseRangeCommandMapper->GenerateCommand(validArgument), std::exception);
}