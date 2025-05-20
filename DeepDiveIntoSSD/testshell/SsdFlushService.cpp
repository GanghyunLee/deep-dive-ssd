#include "SsdFlushService.h"

SsdFlushResult SsdFlushService::Flush()
{
	return _ssdController->Flush();
}
