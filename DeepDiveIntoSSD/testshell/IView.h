#pragma once
#include <iosfwd>
#include <iostream>

#include "ILogger.h"

class IView
{
public:
	virtual ~IView() = default;

public:
	virtual void Render(std::shared_ptr<ILogger>& logger) = 0;
};

