#include "SsdFullWriteService.h"

std::vector<SsdWriteResult> SsdFullWriteService::FullWrite(unsigned int data)
{
	std::vector<SsdWriteResult> result;

	for (int i = 0; i <= MAX_LBA; i++)
	{
		SsdWriteResult ssdWriteResult = _ssdController->Write(i, data);
		result.push_back(ssdWriteResult);

		if (ssdWriteResult.GetTestResult() == false)
			break;
	}

	return result;
}
