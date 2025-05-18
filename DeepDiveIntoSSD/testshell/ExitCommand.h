#pragma once
#include "ICommand.h"

class ExitCommand : public ICommand
{
public:
	~ExitCommand() override = default;
	IView* Execute() override;
	bool NeedToExitAfterExecute() override;
};

