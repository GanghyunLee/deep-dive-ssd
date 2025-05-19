#include "FullWriteAndReadCompareTestScriptService.h"

bool FullWriteAndReadCompareTestScriptService::Execute()
{
	unsigned int writtenValue = 0x1234ABCD;
	unsigned int startLBA = 0;

	while (startLBA < MAX_LBA)
	{
		unsigned int endLBA = startLBA + 4;
		if (endLBA >= MAX_LBA)
			endLBA = MAX_LBA;

		if (startLBA == endLBA)
			break;

		if (false == WriteValueToLbaArea(startLBA, endLBA, writtenValue))
			return false;

		if (false == ReadCompareToLbaArea(startLBA, endLBA, writtenValue))
			return false;

		writtenValue++;
		startLBA += 4;
	}

	return true;
}

bool FullWriteAndReadCompareTestScriptService::WriteValueToLbaArea(int startLba, int endLba, unsigned int data)
{
	// 0 ~4번 LBA까지 Write 명령어를 수행한다.
	for (int lba = startLba; lba <= endLba; lba++)
	{
		if (_ssdController->Write(lba, data).GetTestResult() == false)
			return false;
	}
	return true;
}

bool FullWriteAndReadCompareTestScriptService::ReadCompareToLbaArea(int startLba, int endLba, unsigned int data)
{
	for (int lba = startLba; lba <= endLba; lba++)
	{
		SsdReadResult ssdReadResult = _ssdController->Read(lba);
		if (ssdReadResult.GetTestResult() == false)
			return false;

		if (ssdReadResult.GetData() != data)
			return false;
	}

	return true;
}
