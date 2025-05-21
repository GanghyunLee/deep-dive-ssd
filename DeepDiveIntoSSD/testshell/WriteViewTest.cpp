#include "InMemoryLogger.h"
#include "WriteView.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;

class WriteViewTestFixture : public Test
{
public:
	~WriteViewTestFixture() override = default;

public:
	std::ostringstream _ostream;
	std::shared_ptr<ILogger> _inMemoryLogger = std::make_shared<InMemoryLogger>(_ostream);
};

TEST_F(WriteViewTestFixture, SSDWritePassCaseTest)
{
	SsdWriteResult writeCommandResult = SsdWriteResult::From(true);
	WriteView writeView{writeCommandResult};
	writeView.Render(_inMemoryLogger);

	EXPECT_EQ(_ostream.str(), "[Write] Done");
}

TEST_F(WriteViewTestFixture, SSDWriteFailCaseTest)
{
	SsdWriteResult writeCommandResult = SsdWriteResult::From(false);
	WriteView writeView{ writeCommandResult };
	writeView.Render(_inMemoryLogger);

	EXPECT_EQ(_ostream.str(), "[Write] Error");
}