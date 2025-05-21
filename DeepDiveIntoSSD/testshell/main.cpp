#pragma comment(lib, "testshell-core.lib")

#include <memory>
#include "IoC.h"
#include "Logger.h"
#include "RunnerApplication.h"
#include "TestShellApplication.h"

#define APPLICATION_NO_ERROR (0)
#define APPLICATION_ERROR (1)

int main(int argc, char* argv[])
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	IoC ioc{};
	std::shared_ptr<AbstractTestShellApplication> app;

	if (argc == 1)
		app = std::make_shared<TestShellApplication>(ioc.GetCommandMappers(), std::cin, ioc.GetLogger());
	else if (argc == 2)
		app = std::make_shared<RunnerApplication>(ioc.GetCommandMappers(), std::cin, ioc.GetLogger());
	else
		return APPLICATION_ERROR;

	return (app->Run(argc, argv)) ? APPLICATION_NO_ERROR : APPLICATION_ERROR;
}