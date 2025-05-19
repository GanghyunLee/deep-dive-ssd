#pragma once
#include <memory>
#include <vector>

#include "AbstractTestScriptService.h"
#include "ISsdController.h"

class FullWriteAndReadCompareTestScriptService : public AbstractTestScriptService
{
	enum
	{
		MAX_LBA = 99
	};

public:
	FullWriteAndReadCompareTestScriptService(std::shared_ptr<ISsdController> ssdController) : AbstractTestScriptService(ssdController)
	{
	}

	virtual ~FullWriteAndReadCompareTestScriptService() = default;

public:
	virtual bool Execute();
};

