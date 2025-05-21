#pragma once
#include "HelpView.h"
#include "ICommand.h"

class HelpCommand : public ICommand
{
public:
	~HelpCommand() override = default;

public:
	std::shared_ptr<IView> Execute() override { return std::make_shared<HelpView>(); }
};

