#include "ICommandMapper.h"
#include "gmock/gmock.h"
#include <ostream>
#include "SsdReadService.h"
#include "ReadView.h"
#include "ReadCommand.h"

using namespace std;
using namespace testing;

class MockSsdReadService : public SsdReadService
{
public:
	MockSsdReadService() : SsdReadService(nullptr) {}
	~MockSsdReadService() override = default;

public:
	MOCK_METHOD(SsdReadResult, Read, (int), (override));
};

class ReadCommandTestFixture : public Test
{
public:
	void SetUp() override
	{
		mockSsdReadService = make_shared<MockSsdReadService>();
		readCommand = make_shared<ReadCommand>(mockSsdReadService, lba);
	}

public:
	const int lba = 3;
	std::shared_ptr<ReadCommand> readCommand = nullptr;
	std::shared_ptr<MockSsdReadService> mockSsdReadService = nullptr;
};

TEST_F(ReadCommandTestFixture, GetterSetterTest)
{
	EXPECT_EQ(readCommand->GetLba(), lba);
}

TEST_F(ReadCommandTestFixture, WriteCommandMustReturnWriteView)
{
	EXPECT_CALL(*mockSsdReadService, Read(_))
		.Times(1)
		.WillRepeatedly(Return(SsdReadResult::From(true)));

	shared_ptr<ReadView> view = dynamic_pointer_cast<ReadView>(readCommand->Execute());
	EXPECT_TRUE(view != nullptr);
}