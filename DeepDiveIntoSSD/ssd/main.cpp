#include "gmock/gmock.h"
#include "Ssd.h"

int main(void)
{
#ifdef _DEBUG
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}