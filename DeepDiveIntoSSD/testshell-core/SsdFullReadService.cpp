#include "SsdFullReadService.h"

#include "Constants.h"

std::vector<SsdReadResult> SsdFullReadService::FullRead()
{
	std::vector<SsdReadResult> result;

	for (int i = 0; i <= Constants::MAX_LBA; i++)
	{
		SsdReadResult ssdReadResult = _ssdController->Read(i);
		result.push_back(ssdReadResult);

		if (ssdReadResult.GetTestResult() == false)
			break;
	}

	return result;
}
