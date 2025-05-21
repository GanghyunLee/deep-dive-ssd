#include "ICommandMapper.h"
#include "gmock/gmock.h"
#include <ostream>
#include "ISsdController.h"
#include "SsdWriteService.h"
#include "WriteView.h"
#include "WriteCommand.h"

using namespace std;
using namespace testing;

class MockSsdWriteService : public SsdWriteService
{
public:
	MockSsdWriteService() : SsdWriteService(nullptr) { }
	~MockSsdWriteService() override = default;

public:
	MOCK_METHOD(SsdWriteResult, Write, (int, unsigned int), (override));
};

class WriteCommandTestFixture : public Test
{
public:
	void SetUp() override
	{
		mockSsdWriteService = make_shared<MockSsdWriteService>();
		writeCommand = make_shared<WriteCommand>(mockSsdWriteService, lba, data);
	}

public:
	const int lba = 3;
	const unsigned int data = 9;
	std::shared_ptr<WriteCommand> writeCommand = nullptr;
	std::shared_ptr<MockSsdWriteService> mockSsdWriteService = nullptr;
};

TEST_F(WriteCommandTestFixture, GetterSetterTest)
{
	EXPECT_EQ(writeCommand->GetLba(), lba);
	EXPECT_EQ(writeCommand->GetData(), data);
}

TEST_F(WriteCommandTestFixture, WriteCommandMustReturnWriteView)
{
	EXPECT_CALL(*mockSsdWriteService, Write(_, _))
		.Times(1)
		.WillRepeatedly(Return(SsdWriteResult::From(true)));

	shared_ptr<WriteView> view = dynamic_pointer_cast<WriteView>(writeCommand->Execute());
	EXPECT_TRUE(view != nullptr);
}