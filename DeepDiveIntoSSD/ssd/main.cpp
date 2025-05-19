#include "gmock/gmock.h"
#include "Ssd.h"

int main(int argc, char* argv[])
{

#ifdef _DEBUG
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
#else
	Reader reader;
	Writer writer;
	ArgManager argManager;
	SSD ssd(&reader, &writer, &argManager);
	ssd.run(argc - 1, argv + 1);
	return 0;
#endif
}