#pragma once
#include <iosfwd>

class IView
{
public:
	virtual ~IView() = default;

public:
	virtual void Render(std::ostream& os) = 0;
};

