#include "EraseRangeCommand.h"
#include "EraseView.h"

std::shared_ptr<IView> EraseRangeCommand::Execute()
{
	SsdEraseResult ssdEraseResult = _ssdEraseService->EraseRange(_startLba, _endLba);
	return std::make_shared<EraseView>(ssdEraseResult);
}
