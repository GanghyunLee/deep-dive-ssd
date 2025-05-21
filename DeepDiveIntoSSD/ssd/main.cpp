#pragma comment(lib, "ssd-core.lib")

#include "Ssd.h"

int main(int argc, char* argv[])
{
	SSD& ssd = SSD::getInstance();
	ssd.run(argc - 1, argv + 1);
	return 0;
}