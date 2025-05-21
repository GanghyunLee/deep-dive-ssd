#pragma once
#include "IView.h"

class HelpView : public IView
{
public:
	~HelpView() override = default;

	void Render(std::shared_ptr<ILogger>& logger) override;
};
