#pragma once
#include <string>
#include "IView.h"
#include "SsdEraseResult.h"

class EraseView : public IView
{
public:
	EraseView(const SsdEraseResult& eraseCommandResult) : _eraseCommandResult(eraseCommandResult) {}
	~EraseView() override = default;

	void Render(std::shared_ptr<ILogger>& logger) override;

private:
	SsdEraseResult _eraseCommandResult;
	const std::string STR_PRINT_RESULT_PREFIX = "[Erase]";
	const std::string STR_PRINT_RESULT_DONE = "Done";
	const std::string STR_PRINT_RESULT_ERROR = "Error";
	const std::string STR_CLASS_NAME_ERASEVIEW = "EraseView";
};
