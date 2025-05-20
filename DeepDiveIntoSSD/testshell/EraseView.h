#pragma once
#include <string>
#include "IView.h"
#include "SsdEraseResult.h"

class EraseView : public IView
{
public:
	EraseView(const SsdEraseResult& eraseCommandResult) : _eraseCommandResult(eraseCommandResult) {}
	~EraseView() override = default;

	void Render(std::ostream& os) override;

private:
	SsdEraseResult _eraseCommandResult;
	const std::string STR_PRINT_RESULT_PREFIX = "[Erase]";
};
