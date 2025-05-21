#include "FlushView.h"
#include <sstream>

void FlushView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << STR_PRINT_RESULT_PREFIX << " ";

	if (_flushCommandResult.GetTestResult())
		ss << STR_PRINT_RESULT_DONE;
	else
		ss << STR_PRINT_RESULT_ERROR;

	logger->print(STR_CLASS_NAME_FLUSHVIEW, __FUNCTION__, ss.str());
}
