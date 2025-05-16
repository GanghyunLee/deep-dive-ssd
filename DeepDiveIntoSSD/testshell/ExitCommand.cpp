#include "ExitCommand.h"

IView* ExitCommand::Execute()
{
	return nullptr;
}

bool ExitCommand::NeedToExitAfterExecute()
{
	return true;
}
