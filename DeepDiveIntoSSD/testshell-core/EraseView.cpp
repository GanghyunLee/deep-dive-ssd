#include "EraseView.h"
#include <sstream>

void EraseView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << STR_PRINT_RESULT_PREFIX << " ";

	if (_eraseCommandResult.GetTestResult())
		ss << STR_PRINT_RESULT_DONE;
	else
		ss << STR_PRINT_RESULT_ERROR;

	ss << '\n';

	logger->print(STR_CLASS_NAME_ERASEVIEW, __FUNCTION__, ss.str());
}
