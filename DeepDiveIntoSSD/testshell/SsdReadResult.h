#pragma once
struct SsdReadResult
{
private:
	SsdReadResult(bool testResult, int lba, unsigned int data) : _testResult(testResult), _lba(lba), _data(data)
	{
	}

public:
	static SsdReadResult From(bool testResult)
	{
		return From(testResult, 0, 0);
	}

	static SsdReadResult From(bool testResult, int lba, unsigned int data)
	{
		return SsdReadResult{
			testResult,
			lba,
			data
		};
	}

public:
	bool GetTestResult() const { return _testResult; }
	int GetLba() const { return _lba; }
	unsigned int GetData() const { return _data; }

protected:
	bool _testResult;
	int _lba;
	unsigned int _data;
};

