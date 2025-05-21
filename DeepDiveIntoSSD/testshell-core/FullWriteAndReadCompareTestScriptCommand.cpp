#include "FullWriteAndReadCompareTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> FullWriteAndReadCompareTestScriptCommand::GetView()
{
	return std::make_shared<TestScriptView>(_scriptCommandResult);
}
