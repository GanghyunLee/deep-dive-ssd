#pragma once
#include "IView.h"

class TestScriptView : public IView
{
public:
	TestScriptView(bool testResult) : _testResult(testResult) { }
	~TestScriptView() override = default;

	void Render(std::ostream& os) override;

protected:
	bool _testResult;
};

