#include "EraseView.h"
#include <sstream>

void EraseView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;
	ss << STR_PRINT_RESULT_PREFIX << " ";

	if (_eraseCommandResult.GetTestResult())
		ss << "Done";
	else
		ss << "Error";

	ss << '\n';

	logger->print("EraseView", __FUNCTION__, ss.str());
}
