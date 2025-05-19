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
	MockWriteCommand() : WriteCommand(nullptr, 0, 0) {}
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
			return make_shared<MockWriteCommand>();
		});
	}

public:
	std::shared_ptr<WriteCommandMapper> writeCommandMapper = nullptr;
};

TEST_F(WriteCommandMapperTestFixture, ValidArgumentTest)
{
	std::vector<std::string> validArgument{ "w", "3", "0xAAAABBBB" };
	EXPECT_TRUE(writeCommandMapper->IsSupport(validArgument));
}

TEST_F(WriteCommandMapperTestFixture, MissingLbaCaseTest)
{
	std::vector<std::string> invalidArgument{ "w", "0xAAAABBBB" };
	EXPECT_TRUE(writeCommandMapper->IsSupport(invalidArgument));
}

TEST_F(WriteCommandMapperTestFixture, MissingDataTest)
{
	std::vector<std::string> invalidArgument{ "w", "2" };
	EXPECT_TRUE(writeCommandMapper->IsSupport(invalidArgument));
}

TEST_F(WriteCommandMapperTestFixture, MissingAllParametersTest)
{
	std::vector<std::string> invalidArgument{ "w" };
	EXPECT_TRUE(writeCommandMapper->IsSupport(invalidArgument));
}