#pragma once
struct WriteCommandResultDto
{
private:
	WriteCommandResultDto(bool testResult) : _testResult(testResult)
	{
	}

public:
	static WriteCommandResultDto From(bool testResult)
	{
		return WriteCommandResultDto{
			testResult
		};
	}

public:
	bool GetTestResult() const { return _testResult; }

protected:
	bool _testResult;
};

