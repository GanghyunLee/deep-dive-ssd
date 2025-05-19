#include "FullWriteCommand.h"

#include "FullWriteView.h"

std::shared_ptr<IView> FullWriteCommand::Execute()
{
	std::vector<SsdWriteResult> ssdWriteResults = _ssdFullWriteService->FullWrite(_data);
	return std::make_shared<FullWriteView>(ssdWriteResults);
}
