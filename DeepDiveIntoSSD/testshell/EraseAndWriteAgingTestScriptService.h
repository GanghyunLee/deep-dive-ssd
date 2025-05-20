#pragma once
#include <memory>

#include "AbstractTestScriptService.h"
#include "ISsdController.h"

class EraseAndWriteAgingTestScriptService : public AbstractTestScriptService
{
	enum
	{
		LOOP_COUNT = 30,
		LOCAL_TEST_ERASE_LBA_SIZE = 3,
		LOCAL_TEST_WRITE_LBA_INCREASE_SIZE = 2,
	};

public:
	EraseAndWriteAgingTestScriptService(std::shared_ptr<ISsdController> ssdController) : AbstractTestScriptService(ssdController)
	{
	}

	~EraseAndWriteAgingTestScriptService() override = default;

public:
	bool Execute() override;
};
