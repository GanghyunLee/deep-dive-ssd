#pragma once
struct SsdWriteResult
{
private:
	SsdWriteResult(bool testResult) : _testResult(testResult)
	{
	}

public:
	static SsdWriteResult From(bool testResult)
	{
		return SsdWriteResult{
			testResult
		};
	}

public:
	bool GetTestResult() const { return _testResult; }

protected:
	bool _testResult;
};

