#pragma once
#include <string>
#include "IView.h"
#include "SsdFlushResult.h"

class FlushView : public IView
{
public:
	FlushView(const SsdFlushResult& flushCommandResult) : _flushCommandResult(flushCommandResult) {}
	~FlushView() override = default;

	void Render(std::shared_ptr<ILogger>& logger) override;

private:
	SsdFlushResult _flushCommandResult;
	const std::string STR_PRINT_RESULT_PREFIX = "[Flush]";
	const std::string STR_PRINT_RESULT_DONE = "Done";
	const std::string STR_PRINT_RESULT_ERROR = "Error";
	const std::string STR_CLASS_NAME_FLUSHVIEW = "FlushView";
};
