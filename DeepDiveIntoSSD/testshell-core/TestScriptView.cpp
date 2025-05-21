#include "TestScriptView.h"
#include <sstream>

void TestScriptView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;

	if (_testResult)
		ss << STR_PRINT_RESULT_PASS;
	else
		ss << STR_PRINT_RESULT_FAIL;

	logger->print(STR_CLASS_NAME_TESTSCRIPTVIEW, __FUNCTION__, ss.str());
}
