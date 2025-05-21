#include "TestScriptView.h"
#include <sstream>

void TestScriptView::Render(std::shared_ptr<ILogger>& logger)
{
	std::stringstream ss;

	if (_testResult)
		ss << "Pass";
	else
		ss << "Fail";

	logger->print("TestScriptView", __FUNCTION__, ss.str());
}
