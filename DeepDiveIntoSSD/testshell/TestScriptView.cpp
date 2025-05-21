#include "TestScriptView.h"

void TestScriptView::Render(std::ostream& os)
{
	if (_testResult)
		os << "Pass";
	else
		os << "Fail";
}
