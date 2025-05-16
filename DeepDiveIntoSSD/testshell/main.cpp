#include "TestShellApplication.h"
#include "gmock/gmock.h"

int main(void)
{
#ifdef _DEBUG
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#elif
	IoC ioc{};
	return (true == TestShellApplication{ ioc, std::cin, std::cout }.Run());
#endif
}