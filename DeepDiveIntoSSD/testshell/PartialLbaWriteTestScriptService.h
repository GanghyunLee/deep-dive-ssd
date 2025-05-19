#pragma once
#include <memory>
#include <vector>

#include "AbstractTestScriptService.h"
#include "ISsdController.h"

class PartialLbaWriteTestScriptService : public AbstractTestScriptService
{
public:
	PartialLbaWriteTestScriptService(std::shared_ptr<ISsdController> ssdController) : AbstractTestScriptService(ssdController)
	{
	}

	~PartialLbaWriteTestScriptService() override = default;

public:
	bool Execute() override;
};

