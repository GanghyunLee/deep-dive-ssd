#include "WriteReadAgingTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> WriteReadAgingTestScriptCommand::Execute()
{
	bool result = _ssdScriptService->Execute();
	return std::make_shared<TestScriptView>(result);
}
