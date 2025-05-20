#include "SsdEraseService.h"

SsdEraseResult SsdEraseService::Erase(int lba, int size)
{
	return _ssdController->Erase(lba, size);
}
