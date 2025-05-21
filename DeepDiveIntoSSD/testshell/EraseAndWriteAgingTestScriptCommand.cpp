#include "EraseAndWriteAgingTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> EraseAndWriteAgingTestScriptCommand::GetView()
{
	return std::make_shared<TestScriptView>(_scriptCommandResult);
}
