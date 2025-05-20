#include "EraseView.h"

void EraseView::Render(std::ostream& os)
{
	os << STR_PRINT_RESULT_PREFIX << " ";

	if (_eraseCommandResult.GetTestResult())
		os << "Done";
	else
		os << "Error";
}
