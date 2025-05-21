#pragma once
#include "IView.h"

class TestScriptView : public IView
{
public:
	TestScriptView(bool testResult) : _testResult(testResult) { }
	~TestScriptView() override = default;

	void Render(std::shared_ptr<ILogger>& logger) override;

protected:
	bool _testResult;
private:
	const std::string STR_PRINT_RESULT_PASS = "Pass";
	const std::string STR_PRINT_RESULT_FAIL = "Fail";
	const std::string STR_CLASS_NAME_TESTSCRIPTVIEW = "TestScriptView";
};

