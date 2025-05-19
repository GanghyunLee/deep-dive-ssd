#include "PartialLBAWriteTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> PartialLBAWriteTestScriptCommand::Execute()
{
	bool result = _ssdScriptService->Execute();
	return std::make_shared<TestScriptView>(result);
}
