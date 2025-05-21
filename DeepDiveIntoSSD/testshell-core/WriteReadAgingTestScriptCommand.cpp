#include "WriteReadAgingTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> WriteReadAgingTestScriptCommand::GetView()
{
	return std::make_shared<TestScriptView>(_scriptCommandResult);
}
