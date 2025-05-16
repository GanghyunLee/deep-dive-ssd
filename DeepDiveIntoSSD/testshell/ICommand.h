#pragma once
#include "IView.h"

class ICommand
{
public:
	virtual ~ICommand() = default;

public:
	virtual IView* Execute() = 0;
};

