#include "FlushView.h"

void FlushView::Render(std::ostream& os)
{
	os << STR_PRINT_RESULT_PREFIX << " ";

	if (_flushCommandResult.GetTestResult())
		os << "Done";
	else
		os << "Error";
}
