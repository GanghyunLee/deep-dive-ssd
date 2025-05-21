#include "AbstractTestScriptService.h"

bool AbstractTestScriptService::WriteValueToLbaArea(int startLba, int endLba, unsigned int data)
{
	// 0 ~4번 LBA까지 Write 명령어를 수행한다.
	for (int lba = startLba; lba <= endLba; lba++)
	{
		if (_ssdController->Write(lba, data).GetTestResult() == false)
			return false;
	}
	return true;
}

bool AbstractTestScriptService::ReadCompareToLbaArea(int startLba, int endLba, unsigned int data)
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
