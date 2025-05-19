#include "SsdWriteService.h"

SsdWriteResult SsdWriteService::Write(int lba, unsigned int data)
{
	return _ssdController->Write(lba, data);
}
