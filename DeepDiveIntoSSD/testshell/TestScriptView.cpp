#include "TestScriptView.h"

void TestScriptView::Render(std::ostream& os)
{
	if (_testResult)
		os << "PASS";
	else
		os << "FAIL";
}
