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
};

TEST_F(WriteViewTestFixture, SSDWritePassCaseTest)
{
	WriteCommandResultDto writeCommandResult = WriteCommandResultDto::From(true);
	WriteView writeView{writeCommandResult};
	writeView.Render(_ostream);

	EXPECT_EQ(_ostream.str(), "[Write] Done");
}

TEST_F(WriteViewTestFixture, SSDWriteFailCaseTest)
{
	WriteCommandResultDto writeCommandResult = WriteCommandResultDto::From(false);
	WriteView writeView{ writeCommandResult };
	writeView.Render(_ostream);

	EXPECT_EQ(_ostream.str(), "[Write] Error");
}