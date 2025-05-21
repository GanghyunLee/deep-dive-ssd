#pragma once
#include "IView.h"

class HelpView : public IView
{
public:
	~HelpView() override = default;

public:
	void Render(std::shared_ptr<ILogger>& logger) override;

private:
	const std::string STR_CLASS_NAME_HELPVIEW = "HelpView";
};
