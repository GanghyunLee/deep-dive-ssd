#include "gmock/gmock.h"
#include <ostream>
#include "ISsdController.h"
#include "MockSsdControler.h"
#include "SsdWriteService.h"

using namespace std;
using namespace testing;


TEST(SsdWriteServieTest, SsdWriteServiceTest)
{
	std::shared_ptr<MockSsdController> mockSsdController =
		std::make_shared<MockSsdController>();

	std::shared_ptr<SsdWriteService> ssdWriteService =
		std::make_shared<SsdWriteService>(mockSsdController);

	EXPECT_CALL(*mockSsdController, Write(_, _))
		.Times(1)
		.WillOnce(Return(SsdWriteResult::From(true)));

	EXPECT_CALL(*mockSsdController, Read(_))
		.Times(0);

	EXPECT_EQ(ssdWriteService->Write(3, 0xABABABAB).GetTestResult(), true);
}