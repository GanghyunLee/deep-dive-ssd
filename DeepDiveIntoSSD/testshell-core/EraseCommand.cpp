#include "EraseCommand.h"
#include "EraseView.h"

std::shared_ptr<IView> EraseCommand::Execute()
{
	SsdEraseResult ssdEraseResult = _ssdEraseService->Erase(_lba, _size);
	return std::make_shared<EraseView>(ssdEraseResult);
}
