#include "WriteView.h"
#include <sstream>

void WriteView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << STR_PRINT_RESULT_PREFIX << " ";

	if (_writeCommandResult.GetTestResult())
		ss << "Done";
	else
		ss << "Error";

	logger->print("WriteView", __FUNCTION__, ss.str());
}
