#pragma once
struct SsdEraseResult
{
private:
	SsdEraseResult(bool testResult) : _testResult(testResult)
	{
	}

public:
	static SsdEraseResult From(bool testResult)
	{
		return SsdEraseResult{
			testResult
		};
	}

public:
	bool GetTestResult() const { return _testResult; }

protected:
	bool _testResult;
};

