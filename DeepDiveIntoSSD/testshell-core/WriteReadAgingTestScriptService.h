#pragma once
#include <memory>
#include <vector>

#include "AbstractTestScriptService.h"
#include "ISsdController.h"

class WriteReadAgingTestScriptService : public AbstractTestScriptService
{
	enum
	{
		TEST_LOOP_COUNT = 200,
	};

public:
	WriteReadAgingTestScriptService(std::shared_ptr<ISsdController> ssdController) : AbstractTestScriptService(ssdController)
	{
	}

	~WriteReadAgingTestScriptService() override = default;

public:
	bool Execute() override;
};

