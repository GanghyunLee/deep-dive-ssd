#include "SsdReadService.h"

SsdReadResult SsdReadService::Read(int lba)
{
	return _ssdController->Read(lba);
}