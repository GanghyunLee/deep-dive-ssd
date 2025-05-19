#include "ReadCommand.h"
#include "SsdReadService.h"
#include "ReadView.h"

std::shared_ptr<IView> ReadCommand::Execute()
{
	SsdReadResult ssdReadResult = _ssdReadService->Read(_lba);
	return std::make_shared<ReadView>(ssdReadResult);
}
