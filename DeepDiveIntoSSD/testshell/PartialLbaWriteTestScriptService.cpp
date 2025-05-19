#include "PartialLbaWriteTestScriptService.h"

bool PartialLbaWriteTestScriptService::Execute()
{
	unsigned int writtenValue = 0x4321DCAB;

	// 4번LBA에값을적는다.
	// 0번LBA에같은값을적는다.
	// 3번LBA에같은값을적는다.
	// 1번LBA에같은값을적는다.
	// 2번LBA에같은값을적는다.
	std::vector<int> targetLbas = { 4, 0, 3, 1, 2 };

	for (const auto& targetLba : targetLbas)
	{
		if (false == WriteValueToLbaArea(targetLba, targetLba, writtenValue))
			return false;
	}

	// LBA 0 ~4번, ReadCompare
	return ReadCompareToLbaArea(0, 4, writtenValue);
}
