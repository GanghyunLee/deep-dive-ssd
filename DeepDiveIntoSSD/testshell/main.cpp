#include <memory>
#include "IoC.h"
#include "TestShellApplication.h"
#include "gmock/gmock.h"

#define APPLICATION_NO_ERROR (0)
#define APPLICATION_ERROR (1)

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

#ifdef _DEBUG
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	IoC ioc{};
	std::shared_ptr<TestShellApplication> app = std::make_shared<TestShellApplication>(ioc.GetCommandMappers(), std::cin, std::cout );

	return (app->Run()) ? APPLICATION_NO_ERROR : APPLICATION_ERROR;
#endif
}