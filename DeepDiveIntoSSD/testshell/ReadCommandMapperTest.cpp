#include "gmock/gmock.h"
#include <ostream>
#include <memory>
#include "ReadCommand.h"
#include "ReadCommandMapper.h"

using namespace std;
using namespace testing;

class MockReadCommand : public ReadCommand
{
public:
	MockReadCommand(int lba) : ReadCommand(nullptr, lba) {}
	~MockReadCommand() override = default;

public:
	MOCK_METHOD(std::shared_ptr<IView>, Execute, (), (override));
};

class ReadCommandMapperTestFixture : public Test
{
public:
	~ReadCommandMapperTestFixture() override = default;

public:
	void SetUp() override
	{
		readCommandMapper = std::make_shared<ReadCommandMapper>([&](int lba)
			{
				return make_shared<MockReadCommand>(lba);
			});
	}

public:
	std::shared_ptr<ReadCommandMapper> readCommandMapper = nullptr;
};

TEST_F(ReadCommandMapperTestFixture, ValidArgumentTestForRead)
{
	std::vector<std::string> validArgument{ "read", "2" };
	EXPECT_TRUE(readCommandMapper->IsSupport(validArgument));

	shared_ptr<ReadCommand> cmd = dynamic_pointer_cast<ReadCommand>(readCommandMapper->GenerateCommand(validArgument));
	EXPECT_TRUE(cmd != nullptr);

	EXPECT_EQ(cmd->GetLba(), 2);
}

TEST_F(ReadCommandMapperTestFixture, MissingLbaCaseTestForRead)
{
	std::vector<std::string> invalidArgument{ "read" };
	EXPECT_FALSE(readCommandMapper->IsSupport(invalidArgument));
}