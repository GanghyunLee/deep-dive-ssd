#pragma once
struct SsdFlushResult
{
private:
	SsdFlushResult(bool testResult) : _testResult(testResult)
	{
	}

public:
	static SsdFlushResult From(bool testResult)
	{
		return SsdFlushResult{
			testResult
		};
	}

public:
	bool GetTestResult() const { return _testResult; }

protected:
	bool _testResult;
};

