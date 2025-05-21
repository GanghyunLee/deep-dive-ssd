#include <memory>
#include "gmock/gmock.h"
#pragma comment(lib, "testshell-core.lib")

int main(void)
{
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS(); 
}
