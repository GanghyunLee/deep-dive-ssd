#include "InMemoryLogger.h"
#include "ReadView.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;

class ReadViewTestFixture : public Test
{
public:
	~ReadViewTestFixture() override = default;

public:
	std::ostringstream _ostream;
	std::shared_ptr<ILogger> _inMemoryLogger = std::make_shared<InMemoryLogger>(_ostream);
};

TEST_F(ReadViewTestFixture, SSDReadPassCaseTest1)
{
	SsdReadResult readCommandResult = SsdReadResult::From(true, 0, 0x00000000);
	ReadView readView{ readCommandResult };
	readView.Render(_inMemoryLogger);

	EXPECT_EQ(_ostream.str(), "[Read] LBA 00 : 0x00000000");
}

TEST_F(ReadViewTestFixture, SSDReadPassCaseTest2)
{
	SsdReadResult readCommandResult = SsdReadResult::From(true, 3, 0xAAAABBBB);
	ReadView readView{ readCommandResult };
	readView.Render(_inMemoryLogger);

	EXPECT_EQ(_ostream.str(), "[Read] LBA 03 : 0xAAAABBBB");
}


TEST_F(ReadViewTestFixture, SSDReadFailCaseTest)
{
	SsdReadResult readCommandResult = SsdReadResult::From(false);
	ReadView readView{ readCommandResult };
	readView.Render(_inMemoryLogger);

	EXPECT_EQ(_ostream.str(), "[Read] Error");
}