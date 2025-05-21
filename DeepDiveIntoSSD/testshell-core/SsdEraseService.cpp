#include "SsdEraseService.h"

SsdEraseResult SsdEraseService::Erase(int lba, int size)
{
	return _ssdController->Erase(lba, size);
}

SsdEraseResult SsdEraseService::EraseRange(int startLba, int endLba)
{
	int currentLba = startLba;
	int remainSize = endLba - startLba + 1;

	while (remainSize > 0)
	{
		int eraseAmount = std::min(remainSize, MAX_ERASE_AMOUNT);
		SsdEraseResult localResult = _ssdController->Erase(currentLba, eraseAmount);
		if (false == localResult.GetTestResult())
			return localResult;

		currentLba += eraseAmount;
		remainSize -= eraseAmount;
	}

	return SsdEraseResult::From(true);
}
