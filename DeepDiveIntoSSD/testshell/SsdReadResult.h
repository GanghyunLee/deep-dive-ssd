#pragma once
struct SsdReadResult
{
private:
	SsdReadResult(bool testResult, unsigned int data) : _testResult(testResult), _data(data)
	{
	}

public:
	static SsdReadResult From(bool testResult)
	{
		return From(testResult, 0);
	}

	static SsdReadResult From(bool testResult, unsigned int data)
	{
		return SsdReadResult{
			testResult,
			data
		};
	}

public:
	bool GetTestResult() const { return _testResult; }

protected:
	bool _testResult;
	unsigned int _data;
};

