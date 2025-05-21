#include "gmock/gmock.h"
#include <ostream>
#include <memory>
#include "EraseCommand.h"
#include "EraseCommandMapper.h"

using namespace std;
using namespace testing;

class MockEraseCommand : public EraseCommand
{
public:
	MockEraseCommand(int lba, int size) : EraseCommand(nullptr, lba, size) {}
	~MockEraseCommand() override = default;

public:
	MOCK_METHOD(std::shared_ptr<IView>, Execute, (), (override));
};

class EraseCommandMapperTestFixture : public Test
{
public:
	~EraseCommandMapperTestFixture() override = default;

public:
	void SetUp() override
	{
		eraseCommandMapper = std::make_shared<EraseCommandMapper>([&](int lba, int size)
			{
				return make_shared<MockEraseCommand>(lba, size);
			});
	}

public:
	std::shared_ptr<EraseCommandMapper> eraseCommandMapper = nullptr;
};

TEST_F(EraseCommandMapperTestFixture, ValidArgumentTestWithLargeSize)
{
	std::vector<std::string> validArgument{ "erase", "20", "99999999" };
	EXPECT_TRUE(eraseCommandMapper->IsSupport(validArgument));

	shared_ptr<EraseCommand> cmd = dynamic_pointer_cast<EraseCommand>(eraseCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetLba(), 20);
	EXPECT_EQ(cmd->GetSize(), 80);
}

TEST_F(EraseCommandMapperTestFixture, ValidArgumentTestWithMinusSize)
{
	std::vector<std::string> validArgument{ "erase", "10", "-11" };
	EXPECT_TRUE(eraseCommandMapper->IsSupport(validArgument));

	shared_ptr<EraseCommand> cmd = dynamic_pointer_cast<EraseCommand>(eraseCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetLba(), 0);
	EXPECT_EQ(cmd->GetSize(), 11);
}

TEST_F(EraseCommandMapperTestFixture, ValidArgumentTestWithMinusSize2)
{
	std::vector<std::string> validArgument{ "erase", "0", "-2100000" };
	EXPECT_TRUE(eraseCommandMapper->IsSupport(validArgument));

	shared_ptr<EraseCommand> cmd = dynamic_pointer_cast<EraseCommand>(eraseCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetLba(), 0);
	EXPECT_EQ(cmd->GetSize(), 1);
}

TEST_F(EraseCommandMapperTestFixture, ValidArgumentTestWithMinusSize3)
{
	std::vector<std::string> validArgument{ "erase", "5", "-7" };

	shared_ptr<EraseCommand> cmd = dynamic_pointer_cast<EraseCommand>(eraseCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetLba(), 0);
	EXPECT_EQ(cmd->GetSize(), 6);
}


TEST_F(EraseCommandMapperTestFixture, LbaCannotBeMinus)
{
	std::vector<std::string> invalidArgument{ "erase", "-3", "1" };

	EXPECT_TRUE(eraseCommandMapper->IsSupport(invalidArgument));
	EXPECT_THROW(eraseCommandMapper->GenerateCommand(invalidArgument), std::exception);
}

TEST_F(EraseCommandMapperTestFixture, MissingOneDataTest)
{
	std::vector<std::string> invalidArgument{ "erase", "3" };
	EXPECT_FALSE(eraseCommandMapper->IsSupport(invalidArgument));
}

TEST_F(EraseCommandMapperTestFixture, MissingAllParametersTest)
{
	std::vector<std::string> invalidArgument{ "erase" };
	EXPECT_FALSE(eraseCommandMapper->IsSupport(invalidArgument));
}