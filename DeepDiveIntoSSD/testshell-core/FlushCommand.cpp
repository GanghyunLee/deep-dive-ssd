#include "FlushCommand.h"
#include "FlushView.h"

std::shared_ptr<IView> FlushCommand::Execute()
{
	SsdFlushResult ssdWriteResult = _ssdFlushService->Flush();
	return std::make_shared<FlushView>(ssdWriteResult);
}
