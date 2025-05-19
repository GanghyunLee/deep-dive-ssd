#pragma once
#include <memory>
#include <vector>

#include "AbstractTestScriptService.h"
#include "ISsdController.h"

class FullWriteAndReadCompareTestScriptService : public AbstractTestScriptService
{
public:
	FullWriteAndReadCompareTestScriptService(std::shared_ptr<ISsdController> ssdController) : AbstractTestScriptService(ssdController)
	{
	}

	~FullWriteAndReadCompareTestScriptService() override = default;

public:
	bool Execute() override;
};

