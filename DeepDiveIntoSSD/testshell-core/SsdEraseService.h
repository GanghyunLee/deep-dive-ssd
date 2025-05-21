#pragma once
#include <memory>

#include "ISsdController.h"

class SsdEraseService
{
public:
	SsdEraseService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~SsdEraseService() = default;

public:
	virtual SsdEraseResult Erase(int lba, int size);
	virtual SsdEraseResult EraseRange(int startLba, int endLba);

protected:
	std::shared_ptr<ISsdController> _ssdController;
	const int MAX_ERASE_AMOUNT = 10;
};

