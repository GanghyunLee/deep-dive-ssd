#include "FullReadCommand.h"

#include "FullReadView.h"

std::shared_ptr<IView> FullReadCommand::Execute()
{
	std::vector<SsdReadResult> ssdReadResults = _ssdFullReadService->FullRead();
	return std::make_shared<FullReadView>(ssdReadResults);
}
