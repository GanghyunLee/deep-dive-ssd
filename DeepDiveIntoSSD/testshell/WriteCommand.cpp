#include "WriteCommand.h"
#include "SsdWriteService.h"
#include "WriteView.h"

std::shared_ptr<IView> WriteCommand::Execute()
{
	SsdWriteResult ssdWriteResult = _ssdWriteService->Write(_lba, _data);
	return std::make_shared<WriteView>(ssdWriteResult);
}
