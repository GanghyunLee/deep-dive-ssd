#pragma once
#include "HelpView.h"
#include "ICommand.h"

class HelpCommand : public ICommand
{
public:
	HelpCommand(HelpView* helpView) : _helpView(helpView) { }
	~HelpCommand() override = default;

public:
	IView* Execute() override { return _helpView; }

private:
	HelpView* _helpView;
};

