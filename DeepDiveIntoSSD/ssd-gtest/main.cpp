#pragma comment(lib, "ssd-core.lib")

#include "gmock/gmock.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}