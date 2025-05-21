#include "FlushView.h"
#include <sstream>

void FlushView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << STR_PRINT_RESULT_PREFIX << " ";

	if (_flushCommandResult.GetTestResult())
		ss << "Done";
	else
		ss << "Error";

	logger->print("FlushView", __FUNCTION__, ss.str());
}
