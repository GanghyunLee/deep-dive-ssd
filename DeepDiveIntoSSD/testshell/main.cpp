#include "TestShellApplication.h"
#include "gmock/gmock.h"

int main(void)
{
//#ifdef _DEBUG
//	::testing::InitGoogleMock();
//	return RUN_ALL_TESTS();
//#else
	IoC ioc{};
	return (true == TestShellApplication{ ioc.GetCommandMappers(), std::cin, std::cout }.Run());
//#endif
}