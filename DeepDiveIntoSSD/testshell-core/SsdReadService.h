#pragma once
#include <memory>

#include "ISsdController.h"

class SsdReadService
{
public:
	SsdReadService(std::shared_ptr<ISsdController> ssdController) : _ssdController(ssdController)
	{
	}

	virtual ~SsdReadService() = default;

public:
	virtual SsdReadResult Read(int lba);

protected:
	std::shared_ptr<ISsdController> _ssdController;
};

