#pragma once
#include "IView.h"

class ICommand
{
public:
	virtual ~ICommand() = default;

public:
	// nullptr로 리턴하면 아무것도 출력하지 않는다.
	virtual IView* Execute() = 0;

	// 아래를 true로 리턴하면 수행 후에 종료가 됩니다.
	virtual bool NeedToExitAfterExecute() { return false; }
};

