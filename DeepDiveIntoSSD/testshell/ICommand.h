#pragma once
#include <memory>
#include "IView.h"

class ICommand
{
public:
	virtual ~ICommand() = default;

public:
	// nullptr로 리턴하면 아무것도 출력하지 않는다.
	virtual std::shared_ptr<IView> Execute() = 0;
};

