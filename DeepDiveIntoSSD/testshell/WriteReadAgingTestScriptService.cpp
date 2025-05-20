#include "WriteReadAgingTestScriptService.h"

#include <ctime>

bool WriteReadAgingTestScriptService::Execute()
{
	// Loop 200회
	for (int loop = 0; loop < TEST_LOOP_COUNT; loop++)
	{
		unsigned int randValue = std::rand();

		// 0번 LBA에 랜덤값을적는다.
		if (false == WriteValueToLbaArea(0, 0, randValue))
			return false;

		// 99번 LBA에 랜덤값을적는다.
		if (false == WriteValueToLbaArea(99, 99, randValue))
			return false;

		// LBA 0번과 99번, ReadCompare를 수행
		SsdReadResult lba0Result = _ssdController->Read(0);
		SsdReadResult lba99Result = _ssdController->Read(99);

		if (false == (lba0Result.GetData() == lba99Result.GetData()) &&
			(lba99Result.GetData() == randValue))
			return false;
	}

	return true;
}
