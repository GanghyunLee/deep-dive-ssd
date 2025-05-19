#include "gmock/gmock.h"
#include <ostream>
#include "ISsdController.h"
#include "MockSsdControler.h"
#include "SsdReadService.h"

using namespace std;
using namespace testing;

TEST(SsdReadServieTest, SsdReadServiceTest)
{
	std::shared_ptr<MockSsdController> mockSsdController =
		std::make_shared<MockSsdController>();

	std::shared_ptr<SsdReadService> ssdReadService =
		std::make_shared<SsdReadService>(mockSsdController);

	EXPECT_CALL(*mockSsdController, Read(_))
		.Times(1)
		.WillOnce(Return(SsdReadResult::From(true)));

	EXPECT_CALL(*mockSsdController, Write(_, _))
		.Times(0);

	EXPECT_EQ(ssdReadService->Read(3).GetTestResult(), true);
}