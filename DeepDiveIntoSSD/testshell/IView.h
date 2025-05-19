#pragma once
#include <iosfwd>
#include <iostream>

class IView
{
public:
	virtual ~IView() = default;

public:
	virtual void Render(std::ostream& os) = 0;
};

