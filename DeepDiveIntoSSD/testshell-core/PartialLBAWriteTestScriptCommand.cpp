#include "PartialLBAWriteTestScriptCommand.h"
#include "TestScriptView.h"

std::shared_ptr<IView> PartialLBAWriteTestScriptCommand::GetView()
{
	return std::make_shared<TestScriptView>(_scriptCommandResult);
}
