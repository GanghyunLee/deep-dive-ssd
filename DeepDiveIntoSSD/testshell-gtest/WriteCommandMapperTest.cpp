#include "gmock/gmock.h"
#include <ostream>
#include <memory>
#include "WriteCommand.h"
#include "WriteCommandMapper.h"

using namespace std;
using namespace testing;

class MockWriteCommand : public WriteCommand
{
public:
	MockWriteCommand(int lba, unsigned int data) : WriteCommand(nullptr, lba, data) {}
	~MockWriteCommand() override = default;

public:
	MOCK_METHOD(std::shared_ptr<IView>, Execute, (), (override));
};

class WriteCommandMapperTestFixture : public Test
{
public:
	~WriteCommandMapperTestFixture() override = default;

public:
	void SetUp() override
	{
		writeCommandMapper = std::make_shared<WriteCommandMapper>([&](int lba, unsigned int data)
		{
			return make_shared<MockWriteCommand>(lba, data);
		});
	}

public:
	std::shared_ptr<WriteCommandMapper> writeCommandMapper = nullptr;
};

TEST_F(WriteCommandMapperTestFixture, ValidArgumentTest)
{
	std::vector<std::string> validArgument{ "write", "3", "0xAAAABBBB" };
	EXPECT_TRUE(writeCommandMapper->IsSupport(validArgument));

	shared_ptr<WriteCommand> cmd = dynamic_pointer_cast<WriteCommand>(writeCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetLba(), 3);
	EXPECT_EQ(cmd->GetData(), 2863315899);
}

TEST_F(WriteCommandMapperTestFixture, MissingLbaCaseTest)
{
	std::vector<std::string> invalidArgument{ "write", "0xAAAABBBB" };
	EXPECT_FALSE(writeCommandMapper->IsSupport(invalidArgument));
}

TEST_F(WriteCommandMapperTestFixture, MissingDataTest)
{
	std::vector<std::string> invalidArgument{ "write", "2" };
	EXPECT_FALSE(writeCommandMapper->IsSupport(invalidArgument));
}

TEST_F(WriteCommandMapperTestFixture, MissingAllParametersTest)
{
	std::vector<std::string> invalidArgument{ "write" };
	EXPECT_FALSE(writeCommandMapper->IsSupport(invalidArgument));
}