#include "AbstractScriptCommand.h"

std::shared_ptr<IView> AbstractScriptCommand::Execute()
{
	_scriptCommandResult = _ssdScriptService->Execute();
	return GetView();
}