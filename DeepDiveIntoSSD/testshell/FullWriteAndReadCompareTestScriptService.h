#pragma once
#include <memory>
#include <vector>

#include "ISsdController.h"

class FullWriteAndReadCompareTestScriptService
{
	enum
	{
		MAX_LBA = 99
	};

public:
	FullWriteAndReadCompareTestScriptService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~FullWriteAndReadCompareTestScriptService() = default;

public:
	virtual bool Execute();

protected:
	bool WriteValueToLbaArea(int startLba, int endLba, unsigned int data);
	bool ReadCompareToLbaArea(int startLba, int endLba, unsigned int data);

protected:
	std::shared_ptr<ISsdController> _ssdController;
};

