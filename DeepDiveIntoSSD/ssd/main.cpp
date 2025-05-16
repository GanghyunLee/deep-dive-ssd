#include "gmock/gmock.h"

int main(void)
{
#ifdef _DEBUG
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#elif
	return 0;
#endif
}