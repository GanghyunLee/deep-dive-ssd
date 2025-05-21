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
};

