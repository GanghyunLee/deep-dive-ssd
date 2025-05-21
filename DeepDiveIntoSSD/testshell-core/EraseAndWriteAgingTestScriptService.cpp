#include "EraseAndWriteAgingTestScriptService.h"

#include "Constants.h"

bool EraseAndWriteAgingTestScriptService::Execute()
{
	// 0 ~ 2번 LBA 삭제
	if (false == _ssdController->Erase(0, LOCAL_TEST_ERASE_LBA_SIZE).GetTestResult())
		return false;

	// Loop 30회
	for (int loop = 0; loop < LOOP_COUNT; loop++)
	{
		int startLBA = 2;
		while (startLBA <= Constants::MAX_LBA)
		{
			unsigned int randomData = std::rand();

			int eraseSize = LOCAL_TEST_ERASE_LBA_SIZE;
			if (startLBA + eraseSize - 1 > Constants::MAX_LBA)
				eraseSize = Constants::MAX_LBA - startLBA + 1;

			// Write
			if (false == _ssdController->Write(startLBA, randomData).GetTestResult())
				return false;

			// Overwrite
			if (false == _ssdController->Write(startLBA, randomData).GetTestResult())
				return false;

			// Erase
			if (false == _ssdController->Erase(startLBA, eraseSize).GetTestResult())
				return false;

			startLBA += LOCAL_TEST_WRITE_LBA_INCREASE_SIZE;
		}
	}

	return true;
}
