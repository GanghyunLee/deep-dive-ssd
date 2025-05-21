#pragma once
#include "IView.h"

class HelpView : public IView
{
public:
	~HelpView() override = default;

public:
	void Render(std::shared_ptr<ILogger>& logger) override;
};
