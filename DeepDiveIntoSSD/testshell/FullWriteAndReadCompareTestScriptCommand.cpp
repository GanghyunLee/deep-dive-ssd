#include "FullWriteAndReadCompareTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> FullWriteAndReadCompareTestScriptCommand::Execute()
{
	bool result = _ssdScriptService->Execute();
	return std::make_shared<TestScriptView>(result);
}
