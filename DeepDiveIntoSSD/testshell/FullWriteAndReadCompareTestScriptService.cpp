#include "FullWriteAndReadCompareTestScriptService.h"

bool FullWriteAndReadCompareTestScriptService::Execute()
{
	unsigned int writtenValue = 0x1234ABCD;
	unsigned int startLBA = 0;

	while (startLBA < MAX_LBA)
	{
		unsigned int endLBA = startLBA + 5;
		if (endLBA >= MAX_LBA)
			endLBA = MAX_LBA;

		if (startLBA == endLBA)
			break;

		if (false == WriteValueToLbaArea(startLBA, endLBA, writtenValue))
			return false;

		if (false == ReadCompareToLbaArea(startLBA, endLBA, writtenValue))
			return false;

		writtenValue++;
		startLBA += 5;
	}

	return true;
}
