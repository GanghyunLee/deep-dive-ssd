#include "TestShellApplication.h"
#include "gmock/gmock.h"

int main(void)
{
	IoC ioc{};
	return (true == TestShellApplication{ ioc, std::cin, std::cout }.Run());
}