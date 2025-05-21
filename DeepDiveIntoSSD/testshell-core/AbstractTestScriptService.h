#pragma once
#include <memory>
#include "ISsdController.h"

class AbstractTestScriptService
{
protected:
	enum
	{
		MAX_LBA = 99
	};

public:
	AbstractTestScriptService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~AbstractTestScriptService() = default;

public:
	virtual bool Execute() = 0;

protected:
	bool WriteValueToLbaArea(int startLba, int endLba, unsigned int data);
	bool ReadCompareToLbaArea(int startLba, int endLba, unsigned int data);

protected:
	std::shared_ptr<ISsdController> _ssdController;
};
