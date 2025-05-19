#include "TestShellApplication.h"
#include "gmock/gmock.h"

#define APPLICATION_NO_ERROR (0)
#define APPLICATION_ERROR (1)

int main(void)
{
#ifdef _DEBUG
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	IoC ioc{};
	return (TestShellApplication{ ioc.GetCommandMappers(), std::cin, std::cout }.Run())
		? APPLICATION_NO_ERROR : APPLICATION_ERROR;
#endif
}