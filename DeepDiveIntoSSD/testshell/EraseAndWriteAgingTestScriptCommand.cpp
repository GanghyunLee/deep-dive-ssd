#include "EraseAndWriteAgingTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> EraseAndWriteAgingTestScriptCommand::Execute()
{
	bool result = _ssdScriptService->Execute();
	return std::make_shared<TestScriptView>(result);
}
